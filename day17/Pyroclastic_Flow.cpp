#include <iostream>
#include <fstream>
#include <vector>

//13 long, 2022 rocks

//(2022 / 5) * 13 for length 

typedef enum rocks{
    HORIZONTAL,
    PLUS,
    CORNER,
    VERTICAL,
    SQUARE
};



// ####

// .#.
// ###
// .#.

// ..#
// ..#
// ###

// #
// #
// #
// #

// ##
// ##

std::vector<std::vector<char>> chamber;
std::vector<char> directions;

void start_tetris(rocks rock){

}

int main(){
    std::ifstream input("input");


    std::string line;
    getline(input, line);
    input.close();

    for(int i = 0; i < line.size(); i++){
        directions.push_back(line[i]);
    }

    int len = ((2022 / 5) * 13) + 10;
    while(len) {
        std::vector<char> v;
        v.push_back('|');
        for(int i = 0; i < 7; i++){
            v.push_back('.');
        }
        v.push_back('|');
        chamber.push_back(v);
        len--;
    }
    std::vector<char> bottom;
    bottom.push_back('+');
    for(int i = 0; i < 7; i++){
        bottom.push_back('-');
    }
    bottom.push_back('+');

    int rock_count = 0;
    while(rock_count < 2022){
        for(int i = 0; i < 5; i++){
            start_tetris(i);
            rock_count++;
            if(rock_count == 2022){
                break;
            }
        }
    }


    std::cout << "Final score: " << std::endl;
}