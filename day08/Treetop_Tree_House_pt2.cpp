#include <iostream>
#include <fstream>
#include <vector>

int calculate_score(int x, int y, std::vector<std::vector<int> > forest){

    int height_tree = forest[y][x];
    int score = 1;
    if (x == 0 || x == forest[0].size() - 1 || y == 0 || y == forest.size() - 1){ //outer trees
        return 0;
    }

    int i = 1;
    while(x - i >= 0 && (forest[y][x-i] < height_tree)){     //check left
        i++;
    }
    std::cout << " i " << i << " x " << x << " y " << y << std::endl;
    score *= (i - 1);

    i = 1;
    while(x + i < forest[0].size() && (forest[y][x+i] < height_tree)){ //check right
        i++;
    }
    std::cout << " i " << i << " x " << x << " y " << y << std::endl;
    score *= (i - 1);

    //check up
    i = 0;
    while(y - i > 0){
        i++;
        if(forest[y - i][x] >= height_tree){
            break;
        }
    }
    std::cout << " i " << i << " x " << x << " y " << y << std::endl;
    score *= i;

    //check down
    i = 0;
    while(y + i < forest.size() - 1){
        i++;
        if(forest[y + i][x] >= height_tree){
            break;
        }
    }
    std::cout << " i " << i << " x " << x << " y " << y << std::endl;
    score *= i;

    return score;
}

int main(){
    std::ifstream input("example");
    std::vector<std::vector<int> > forest;

    std::string line;
    do{
        input >> line;
        std::vector<int> row;
        for(char t : line){
            row.push_back(t - '0');
        }
        forest.push_back(row);
    } while(!input.eof());
    input.close();

    int highest_score = 0;

    for(int y = 0; y < forest.size(); y++){
        for(int x = 0; x < forest[0].size(); x++){
            int score = calculate_score(x, y, forest);
            if (score > highest_score){
                highest_score = score;
            }
        }
    }

    std::cout << "highest scenic score: " << highest_score << std::endl;
}