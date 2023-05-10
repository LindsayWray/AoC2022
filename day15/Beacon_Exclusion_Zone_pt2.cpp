#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <stdio.h>

#define MAX 4000000

typedef struct Sensor {
    int x;
    int y;
    int range;
} Sensor;

int manhattan_dist(Sensor& s, int x, int y){
        return abs(s.x - x) + abs(s.y - y);
};

int endOfRange(Sensor& s, int y){
    return s.x + (s.range - abs(s.y - y));
};

int main(){
    std::ifstream input("input");

    std::vector<Sensor> sensors;

    std::string line;
    while(getline(input, line)) {   
        Sensor s;

        int beacon_x;
        int beacon_y;

        sscanf(line.c_str(), "Sensor at x=%d, y=%d: closest beacon is at x=%d, y=%d", &s.x, &s.y, &beacon_x, &beacon_y);

        s.range = manhattan_dist(s, beacon_x, beacon_y);
        sensors.push_back(s);
    };
    input.close();

    for(int y = 0; y <= MAX; y++) {
        for(int x = 0; x <= MAX; x++) {
            bool found = false;
            for(auto &s: sensors) {
                if (manhattan_dist(s, x, y) <= s.range) {
                    x = endOfRange(s, y);
                    found = true;
                    break;
                }
            }
            if (!found){
                std::cout << "Final score: " << (x * 4000000L + y) << std::endl;
                return 0;
            }
        }
    }
}