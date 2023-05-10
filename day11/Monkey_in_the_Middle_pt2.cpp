#include <iostream>
#include <fstream>
#include <deque>
#include <vector>
#include <sstream> 

enum operation { 
    ADD,
    MULTIPLY,
    SQUARED
};

typedef struct Monkey{
    std::deque<size_t> items;
    operation op;
    int op_val;
    int divisible;
    int true_monkey;
    int false_monkey;
    long inspected_items;

} Monkey;

void monkey_business(Monkey &monkey, std::vector<Monkey> &monkeys, size_t lcd){
    while(!monkey.items.empty()){
        
        if(monkey.op == ADD){
            monkey.items.front() += monkey.op_val;
        } else if (monkey.op == MULTIPLY){
            monkey.items.front() *= monkey.op_val;
            
        } else {
            monkey.items.front() = monkey.items.front() * monkey.items.front();
        }
        monkey.items.front() %= lcd;
        if (monkey.items.front() % monkey.divisible == 0){
            monkeys[monkey.true_monkey].items.push_back(monkey.items.front());
        } else {
            
            monkeys[monkey.false_monkey].items.push_back(monkey.items.front());
        }
        monkey.items.pop_front();
        monkey.inspected_items++;
    }
}

int main(){
    std::ifstream input("input");
    std::vector<Monkey> monkeys;
    
    std::string line;
    std::string str;
    int num = 1;
    while(!input.eof()){
        Monkey m;
        getline(input, line, ':');
        getline(input, line, ':');
        getline(input, str, '\n');
        std::stringstream ss(str);
        while(std::getline(ss, line, ',')){
            m.items.push_back(std::stoi(line));
        }

        getline(input, line);
        line = line.substr(23);
        if (line[0] == '+'){
            m.op = ADD;
        } else {
            m.op = MULTIPLY;
        }
        line = line.substr(2);
        
        if(line == "old"){
            m.op = SQUARED;
            m.op_val = 0;
        } else {
            m.op_val = std::stoi(line);
        }
        
        getline(input, line);
        m.divisible = std::stoi(line.substr(21));
        getline(input, line);
        m.true_monkey = std::stoi(line.substr(29));
        getline(input, line);
        m.false_monkey = std::stoi(line.substr(30));
        m.inspected_items = 0;

        monkeys.push_back(m);
    };
    input.close();

    size_t lcd = 1;
    for (auto &m : monkeys){
        lcd *= m.divisible;
    }
    std::cout << lcd << std::endl;

    for( int i = 0; i < 10000; i++){
        for (auto &m : monkeys){
            monkey_business(m, monkeys, lcd);
        }
    }

    std::vector<long> inspected;
    for (auto &m : monkeys){
        std::cout << m.inspected_items << std::endl;
        inspected.push_back(m.inspected_items);
    }

    std::sort(inspected.begin(), inspected.end(), std::greater<long>());

    std::cout << "answer " << inspected[0] * inspected[1] << std::endl;
}