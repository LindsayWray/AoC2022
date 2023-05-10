#include <iostream>
#include <fstream>
#include <vector>

int main(){
    std::ifstream input("input");

    size_t total = 0;
    std::pair<int, int> elf1, elf2;
    do{
        input >> elf1.first;
        input.ignore();
        input >> elf1.second;
        input.ignore();
        input >> elf2.first;
        input.ignore();
        input >> elf2.second;

        if( elf2.first >= elf1.first && elf2.first <= elf1.second || 
            elf2.second >= elf1.first && elf2.second <= elf1.second ||
            elf1.first >= elf2.first && elf1.first <= elf2.second ||
            elf1.second >= elf2.first && elf1.second <= elf2.second) {
            total++;
        }

    }while (!input.eof());
    input.close();

    std::cout << "Final score: " << total << std::endl;
}