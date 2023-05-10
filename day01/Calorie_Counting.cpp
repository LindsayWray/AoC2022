#include <iostream>
#include <fstream>
#include <vector>

int main(){
    std::vector<long> portions;
    std::ifstream input("input");

    std::string str;
    long portion = 0;
    do {
        getline(input, str);
        if (str.empty()) {
            portions.push_back(portion);
            portion = 0;
        } else {
            portion += atoi(str.c_str());
        }
	} while (!input.eof());
	input.close();

    std::sort(portions.begin(), portions.end(), std::greater<int>());
    std::cout << "The three largest amount of total calories: " << portions[0] + portions[1] + portions[2] << std::endl;
}