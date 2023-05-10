#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <set>
#include <sstream>

typedef struct Valve {
    std::string name;
    int index;
    int rate;
    std::vector<std::string> tunnels;
} Valve;

std::map<std::string, Valve> valves;
int bestScore;
std::vector<std::vector<int> > distances;


void findRoute(Valve& valve, int stepsLeft, int score, std::set<std::string> closedValves) {
    if (valve.rate != 0) {
        closedValves.erase(valve.name);
        stepsLeft--;        
        score += stepsLeft * valve.rate;
        if (score > bestScore) {
            bestScore = score;
        }  
    }
    for(auto next: closedValves) {
        int i = valve.index;
        int j = valves[next].index;
        auto distance = distances[i][j];
        if (distance < stepsLeft) {
            findRoute(valves[next], stepsLeft - distance, score, closedValves);
        }
    }
}

int main(){
    std::ifstream input("input");

    std::string line;
    int index = 0;
    while(getline(input, line)) {
        Valve v;
        v.index = index++;

        std::stringstream ss(line);
        ss.ignore(6);
        ss >> v.name;
        ss.ignore(15);
        ss >> v.rate;
        ss.ignore(24);

        std::string tunnel;
        while(ss >> tunnel) {
            v.tunnels.push_back(tunnel.substr(0,2));
        }
        valves[v.name] = v;
    }while (!input.eof());
    input.close();

    int size = valves.size();

    for (int i = 0; i < valves.size(); i++) {
        std::vector<int> row(valves.size(), 1000);
        distances.push_back(row);
    }
    for(auto v: valves) {
        distances[v.second.index][v.second.index] = 0;
        for (auto tunnel: v.second.tunnels) {
            distances[v.second.index][valves[tunnel].index] = 1;
        }
    }
    for(int k = 0; k < distances.size(); k++) {
        for(int i = 0; i < distances.size(); i++) {
            for(int j = 0; j < distances.size(); j++) {
                if (distances[i][j] > distances[i][k] + distances[k][j] ) {
                    distances[i][j] = distances[i][k] + distances[k][j];
                }
            }
        }
    }

    std::set<std::string> usefulValves;
    for(auto v: valves) {
        if (v.second.rate != 0) {
            usefulValves.insert(v.second.name);
        }
    }

    findRoute(valves["AA"], 30, 0, usefulValves);
    
    std::cout << "Final score: " << bestScore << std::endl;
}