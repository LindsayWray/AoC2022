#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <numeric>

typedef struct Dir{
    std::map<std::string, Dir> subDirs;
    std::vector<size_t> files;
} Dir;

size_t answer = 0;

size_t    get_Dir_size(Dir& dir){
    int size = std::accumulate(dir.files.begin(), dir.files.end(), 0); // fancy sum of vec
    for(auto subdir : dir.subDirs){
        size += get_Dir_size(subdir.second);
    }
    return size;
}

void list_directory(std::ifstream &input, std::string line, Dir& dir){
    getline(input, line); // skip, should be "$ ls"
    while(getline(input, line)){
        if (line.find("$ cd ..") == 0){ // go back
            size_t total_dir_size = get_Dir_size(dir);
            if (total_dir_size <= 100000){
                //std::cout << total_dir_size << std::endl;
                answer += total_dir_size;
            }
            return;
        } else if (line.find("$ cd") == 0){ // deeper in dir structure
            list_directory(input, line, dir.subDirs[line.substr(5)]);
        } else if (line.find("dir") == 0){
            dir.subDirs[line.substr(4)];
        } else {
            dir.files.push_back(stoi(line));
        }
    }
}

int main(){
    std::ifstream input("input");

    std::string line;
    getline(input, line);
    Dir root;
    list_directory(input, line, root);
    input.close();

    std::cout << "answer: " << answer << std::endl;
}