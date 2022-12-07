#include <iostream>
#include <fstream>
#include <deque>
#include <vector>

int main(){
    std::ifstream input("input");

    std::vector<std::deque<char> > stacks;
    for (int i = 0; i < 9; i++){
        std::deque<char> s;
        stacks.push_back(s);
    }

    std::string line;
    while(getline(input, line)){
        int len = line.length();
        int idx = 1;
        int stacknum = 0;
        while (idx <= len ){
            if(!isspace(line[idx])){
                stacks[stacknum].push_back(line[idx]);
            } 
            stacknum++;
            idx += 4;
        }
    } 
    input.close();

    std::ifstream input_pt2("input_pt2");

    std::string instruction;
    int move, from, to;
    do{
        input_pt2 >> instruction >> move >> instruction >> from >> instruction >> to;
        
        if (move > 1){
            std::stack<char> stack_holder;
            for(int i = 0; i < move; i++){
                stack_holder.push(stacks[from - 1].front());
                stacks[from - 1].pop_front();
            }
            for(int i = 0; i < move; i++){
                stacks[to - 1].push_front(stack_holder.top());
                stack_holder.pop();
            }  
        } else {
            for(int i = 0; i < move; i++){
                stacks[to - 1].push_front(stacks[from - 1].front());
                stacks[from - 1].pop_front();
            } 
        }
    }while (!input_pt2.eof());
    input_pt2.close();

    std::cout << "Final answer: ";
    for(int i = 0; i < stacks.size(); i++){
        if (!stacks[i].empty()){
            std::cout << stacks[i].front();
        }
    }
    std::cout << std::endl;
}