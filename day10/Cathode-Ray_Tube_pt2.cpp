#include <iostream>
#include <fstream>
#include <vector>

int main(){
    std::ifstream input("input");
    std::vector<long> values;

    long X = 1;
    long cycle = 0;
    values.push_back(X);

    std::string line;
    int v = 0;
    do{
        input >> line;
        if (line == "noop"){
            cycle++;
            values.push_back(X);
        } else {
            cycle++;
            values.push_back(X);
            cycle++;
            values.push_back(X);
            input >> v;
            X += v;
        }

    } while(!input.eof());
    input.close();

    cycle = 1;
    for(int i = 0; i < 6; i++){
        for(int j = 0; j < 40; j++){
            // std::cout << " cycle " << cycle % 40 << ' ' << values[cycle] << ' ';
            // std::cout << values[cycle];
            if((cycle -1 ) % 40 == values[cycle] -1 || (cycle -1 ) % 40 == values[cycle] || (cycle -1 ) % 40 == values[cycle] + 1) {
                std::cout << "#";
            } else {
                std::cout << ".";
            }
            cycle++;
        }
        std::cout << std::endl;
    }

       



    std::cout << "20th " << values[20] << " 60th " << values[60] << " 100th " << values[100] 
                << " 140th " << values[140] << " 180th " << values[180] << " 220th " << values[220] << std::endl;
    std::cout << "the sum of signal strengths " 
                << (values[20] * 20) + (values[60] * 60) + (values[100] * 100) +
                (values[140] * 140) + (values[180] * 180) + (values[220] * 220) << std::endl;
}