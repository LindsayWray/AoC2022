#include <iostream>
#include <fstream>

int main(){
    std::ifstream input("input");

    size_t score = 0;
    char opponent;
    char adviced;

    while(input >> opponent && input >> adviced){
        if (opponent == 'A'){
            if (adviced == 'X'){
                score += 4;
            } else if (adviced == 'Y') {
                score += 8;
            }
            else if (adviced == 'Z') {
                score += 3;
            }
        }
        if (opponent == 'B'){
            if (adviced == 'X'){
                score += 1;
            } else if (adviced == 'Y') {
                score += 5;
            }
            else if (adviced == 'Z') {
                score += 9;
            }
        }
        if (opponent == 'C'){
            if (adviced == 'X'){
                score += 7;
            } else if (adviced == 'Y') {
                score += 2;
            }
            else if (adviced == 'Z') {
                score += 6;
            }
        }
    }
	input.close();

    std::cout << "Final score: " << score << std::endl;
}