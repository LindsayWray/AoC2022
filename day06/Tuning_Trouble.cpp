#include <iostream>
#include <fstream>
#include <unordered_set>

int main(){
    std::ifstream input("input");

    std::string superstring;
    input >> superstring;
    input.close();

    for(int i = 0; i < superstring.size(); i++) {
        std::unordered_set<char> signal;
        int idx = i;
        while(signal.size() < 14){  // 4 for pt_1
            bool not_duplicate = signal.insert(superstring[idx]).second;
            if (!not_duplicate){
                break;
            }
            idx++;
        }
        if (signal.size() == 14) {
            std::cout << " the signal: ";
            for(char character : signal){
                std::cout << character;
            }
            std::cout << std::endl;
            std::cout << "answer " << idx << std::endl;
            return 0;
        }
    }
}