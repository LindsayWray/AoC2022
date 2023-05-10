#include <iostream>
#include <fstream>
#include <vector>

typedef struct Tree {
    Tree(int height) : height(height), visible(false){};

    int height;
    bool visible;
} Tree;

int main(){
    std::ifstream input("input");
    std::vector<std::vector<Tree> > forest;

    std::string line;
    do{
        input >> line;
        std::vector<Tree> row;
        for(char t : line){
            row.emplace_back(t - '0');
        }
        forest.push_back(row);
    } while(!input.eof());
    input.close();

    for(auto &row : forest){
        int highest = -1;
        for(auto &t : row){
            if(t.height > highest){
                t.visible = true;
                highest = t.height;
            }
        }
    }

    for(auto &row : forest){
        int len = row.size();
        int highest = -1;
        for(int i = len - 1; i >=0; i--){
            if(row[i].height > highest){
                row[i].visible = true;
                highest = row[i].height;
            }
        }
    }

    for(int j = 0; j < forest[0].size(); j++){
        int highest = -1;
        for(int i = 0; i < forest.size(); i++){
            if(forest[i][j].height > highest){
                forest[i][j].visible = true;
                highest = forest[i][j].height;
            }
        }
    }

    for(int j = 0; j < forest[0].size(); j++){
        int highest = -1;
        for(int i = forest.size() - 1; i >=0 ; i--){
            if(forest[i][j].height > highest){
                forest[i][j].visible = true;
                highest = forest[i][j].height;
            }
        }
    }

    size_t count = 0;
    for(auto &row : forest){
        for(auto &t : row){
            if(t.visible){
                count++;
            }
        }
    }

    std::cout << "amount of visible trees " << count << std::endl;
}