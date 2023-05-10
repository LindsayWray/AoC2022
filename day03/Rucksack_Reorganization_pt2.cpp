#include <iostream>
#include <fstream>

int main(){
    std::ifstream input("input");

    size_t total = 0;
    std::string rucksack1, rucksack2, rucksack3;

    while(input >> rucksack1 && input >> rucksack2 && input >> rucksack3){
        for(char item : rucksack1){
            if (rucksack2.find(item) != std::string::npos && rucksack3.find(item) != std::string::npos){
                total += isupper(item) ? item - 38 : item - 96;
                break;
            }
        }
    }
    input.close();

    std::cout << "Final score: " << total << std::endl;
}