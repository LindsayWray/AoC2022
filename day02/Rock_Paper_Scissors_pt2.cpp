#include <iostream>
#include <fstream>

int main(){
    std::ifstream input("input");

    size_t score = 0;
    char opponent;
    char adviced;

    while(input >> opponent && input >> adviced) {
        if (opponent == 'A'){
            if (adviced == 'X'){
                score += 3;
            } else if (adviced == 'Y') {
                score += 4;
            }
            else if (adviced == 'Z') {
                score += 8;
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
                score += 2;
            } else if (adviced == 'Y') {
                score += 6;
            }
            else if (adviced == 'Z') {
                score += 7;
            }
        }
	}
	input.close();

    std::cout << "Final score: " << score << std::endl;
}