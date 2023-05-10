#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <stdio.h>

#define Y 2000000

typedef struct Sensor {
    int x;
    int y;
    int range;
} Sensor;

int manhattan_dist(Sensor& s, int x, int y){
        return abs(s.x - x) + abs(s.y - y);
};

int main(){
    std::ifstream input("input");

    std::vector<Sensor> sensors;
    std::set<int> beacon_xs;
    int min_x = 0;
    int max_x = 0;

    std::string line;
    while(getline(input, line)) {   
        Sensor s;

        int beacon_x;
        int beacon_y;

        sscanf(line.c_str(), "Sensor at x=%d, y=%d: closest beacon is at x=%d, y=%d", &s.x, &s.y, &beacon_x, &beacon_y);

        s.range = manhattan_dist(s, beacon_x, beacon_y);
        sensors.push_back(s);

        if (s.x - s.range < min_x) {
            min_x = s.x - s.range;
        }
        if (s.x + s.range > max_x) {
            max_x = s.x + s.range;
        }
        if (beacon_y == Y) {
            beacon_xs.insert(beacon_x);
        }
    };
    input.close();

    int coverage = 0;

    for(int x = min_x; x <= max_x; x++) {
        for(auto &s: sensors) {
            if (manhattan_dist(s, x, Y) <= s.range) {
                coverage++;
                break;
            }
        }
    }


    std::cout << "Final score: " << coverage - beacon_xs.size() << std::endl;
}