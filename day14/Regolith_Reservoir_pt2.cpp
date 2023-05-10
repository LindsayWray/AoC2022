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

bool    falling_sand(){
    coord current(500, 0);

    while(1){
        if(cave[current.y + 1][current.x] == '.'){
            current.y++;
        } else if (cave[current.y + 1][current.x - 1] == '.'){
            current.y++;
            current.x--;
        } else if (cave[current.y + 1][current.x + 1] == '.'){
            current.y++;
            current.x++;
        } else {
            cave[current.y][current.x] = 'O';
            if(current.y == 0 && current.x == 500){
                std::cout << "Sand pyramid is complete\n";
                return false;
            }
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

    for(int y = 0; y < y_max + 2; y++){
        std::vector<char> row(1000, '.');
        cave.push_back(row);
    }
    std::vector<char> row(1000, '#'); // floor
    cave.push_back(row);
    cave[0][500] = '+';

    for(auto path : paths){
        for(int i = 0; i < path.size(); i++){
            cave[path[i].y][path[i].x] = '#';
            if(i != 0){
                if(path[i - 1].x == path[i].x){
                    if(path[i - 1].y < path[i].y){
                        for(int y = path[i - 1].y; y < path[i].y; y++){
                            cave[y][path[i].x] = '#';
                        }
                    } else {
                        for(int y = path[i].y; y < path[i - 1].y; y++){
                            cave[y][path[i].x] = '#';
                        }
                    }
                } else {
                    if(path[i - 1].x < path[i].x){
                        for(int x = path[i - 1].x; x < path[i].x; x++){
                            cave[path[i].y][x] = '#';
                        }
                    } else {
                        for(int x = path[i].x; x < path[i - 1].x; x++){
                            cave[path[i].y][x] = '#';
                        }
                    }

                }
            }
        }
    }

    int sandgrains = 0;
    while(falling_sand()){
        sandgrains++;
    }

    std::cout << "Amount of sand grains: " << sandgrains + 1 << std::endl;
}