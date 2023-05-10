#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

typedef struct coord{
    coord() : x(0), y(0){};
    coord(int x, int y) : x(x), y(y) {};

    int x;
    int y;
} coord;

std::vector<std::vector<char> > cave;

bool    falling_sand(int x_min){
    coord current(500 - x_min , 0);
    
    while(1){
        if(current.y == cave.size() - 1){
            std::cout << "Sand is dropping in the void\n";
            return false;
        } else if(cave[current.y + 1][current.x] == '.'){
            current.y++;
        } else if (current.x == 0){
            std::cout << "Sand is dropping in the void\n";
            return false;
        } else if (cave[current.y + 1][current.x - 1] == '.'){
            current.y++;
            current.x--;
        } else if (current.x == cave[0].size() - 1){
            std::cout << "Sand is dropping in the void\n";
            return false;
        } else if (cave[current.y + 1][current.x + 1] == '.'){
            current.y++;
            current.x++;
        } else {
            cave[current.y][current.x] = 'O';
            return true;
        }
    }

}

int main(){
    std::ifstream input("input");
    std::vector<std::vector<coord> > paths;

    std::string line;
    int x_min = 500, x_max = 0, y_max = 0;
    while(getline(input, line)){
        std::vector<coord> path;
        std::stringstream ss(line);
        while(!ss.eof()){
            coord c;
            ss >> c.x;
            ss.ignore();
            ss >> c.y;
            ss.ignore(4);
            path.push_back(c);
            if(c.x < x_min){
                x_min = c.x;
            }
            if(c.x > x_max){
                x_max = c.x;
            }
            if(c.y > y_max){
                y_max = c.y;
            }
        }
        paths.push_back(path);
    }
    input.close();

    for(int y = 0; y <= y_max; y++){
        std::vector<char> row(x_max - x_min + 1, '.');
        cave.push_back(row);
    }
    cave[0][500 - x_min] = '+';

    for(auto path : paths){
        for(int i = 0; i < path.size(); i++){
            cave[path[i].y][path[i].x - x_min] = '#';
            if(i != 0){
                if(path[i - 1].x == path[i].x){
                    if(path[i - 1].y < path[i].y){
                        for(int y = path[i - 1].y; y < path[i].y; y++){
                            cave[y][path[i].x - x_min] = '#';
                        }
                    } else {
                        for(int y = path[i].y; y < path[i - 1].y; y++){
                            cave[y][path[i].x - x_min] = '#';
                        }
                    }
                } else {
                    if(path[i - 1].x < path[i].x){
                        for(int x = path[i - 1].x; x < path[i].x; x++){
                            cave[path[i].y][x - x_min] = '#';
                        }
                    } else {
                        for(int x = path[i].x; x < path[i - 1].x; x++){
                            cave[path[i].y][x - x_min] = '#';
                        }
                    }

                }
            }
        }
    }

    int sandgrains = 0;
    while(falling_sand(x_min)){
        sandgrains++;
    }

    for(int y = 0; y <= y_max; y++){
        for(int x = 0; x <= x_max - x_min; x++){
            std::cout << cave[y][x];
        }
        std::cout << std::endl;
    }

    std::cout << "Amount of sand grains: " << sandgrains << std::endl;
}