#include <iostream>
#include <fstream>

int main(){
    std::ifstream input("input");

    size_t total = 0;
    std::string rucksack;

    while(input >> rucksack){
        int mid = rucksack.length() / 2;
        std::string first = rucksack.substr(0, mid);
        std::string second = rucksack.substr(mid);

        char item = first[first.find_first_of(second)];
        total += isupper(item) ? item - 38 : item - 96;
    }
    input.close();

    std::cout << "Final score: " << total << std::endl;
}