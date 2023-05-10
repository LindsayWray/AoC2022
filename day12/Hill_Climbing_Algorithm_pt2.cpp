#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <set>
#include <queue>

typedef struct square {
    square(std::pair<int,int> coord) : coord(coord) {};

    int g_cost;
    int h_cost;
    int f_cost;
    std::pair<int,int> coord;
} square;

bool operator>(const square& lhs, const square& rhs) {
    return (lhs.f_cost > rhs.f_cost) ||
        (lhs.f_cost == rhs.f_cost && lhs.h_cost > rhs.h_cost);
}

std::vector<std::vector<char> > grid;
std::set<std::pair<int,int> > closedSet;
std::priority_queue<square, std::vector<square>, std::greater<square> > openSet;


int manhattan_dist(std::pair<int,int> coord, std::pair<int,int> &endGoal_coord){
        return abs(coord.first - endGoal_coord.first) +
            abs(coord.second - endGoal_coord.second);
};

void updateNode(int x, int y, square current) {
    square neighbour(std::make_pair(x, y));
    if(closedSet.count(neighbour.coord))
        return;
    if(y >= 0 && y < grid.size() && x >= 0 && x < grid[0].size() 
            && grid[y][x] >= (grid[current.coord.second][current.coord.first] - 1)) {
        neighbour.g_cost = current.g_cost + 1;
        neighbour.h_cost = 0;
        neighbour.f_cost = neighbour.g_cost + neighbour.h_cost;
        openSet.push(neighbour);
    }   
}

void updateNeighbours(square current) {
    if(closedSet.count(current.coord)) //catches duplicates in openSet
        return;
    updateNode(current.coord.first, current.coord.second - 1, current);      //North
    updateNode(current.coord.first + 1 , current.coord.second, current);     //East
    updateNode(current.coord.first, current.coord.second + 1, current);      //South
    updateNode(current.coord.first - 1, current.coord.second, current);      //West
}

int main(){
    std::ifstream input("input");

    std::string line;
    std::pair<int, int> start_coord;
    std::pair<int, int> end_coord;
    for(int y = 0; std::getline(input, line); y++){
        std::vector<char> row;
        for(int x = 0; x < line.length(); x++){
            if(line[x] == 'S'){
                start_coord = std::make_pair(x,y);
                row.push_back('a');
            }
            else if(line[x] == 'E'){
                end_coord = std::make_pair(x,y);
                row.push_back('z');
            } else {
                row.push_back(line[x]);
            }
        }
        grid.push_back(row);
    }
    input.close();

    square start_square(end_coord); // start from end position
    start_square.g_cost = 0;
    start_square.h_cost =  0;
    start_square.f_cost = start_square.g_cost + start_square.h_cost;
    openSet.push(start_square);

    int steps = 0;
    while(true) {
        steps++;
        square smallest = openSet.top();
        std::cout << smallest.coord.first << " " << smallest.coord.second << std::endl;
        if(grid[smallest.coord.second][smallest.coord.first] == 'a'){
            std::cout   << "Reached destination, minimum required effort is: "
                        << smallest.g_cost
                        << ".\nResult found in " << steps << " step calculations.\n\n";
            break;
        }
        openSet.pop();
        updateNeighbours(smallest);
        closedSet.insert(smallest.coord);
    }  
}