#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <numeric>

typedef struct Dir{
    std::map<std::string, Dir> subDirs;
    std::vector<size_t> files;
} Dir;

std::vector<size_t> dir_sizes;

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
            dir_sizes.push_back(get_Dir_size(dir));
            return;
        } else if (line.find("$ cd") == 0){ // deeper in dir structure
            list_directory(input, line, dir.subDirs[line.substr(5)]);
        } else if (line.find("dir") == 0){
            dir.subDirs[line.substr(4)];
        } else {
            dir.files.push_back(stoi(line));
        }
    }
    dir_sizes.push_back(get_Dir_size(dir));
}

int main(){
    std::ifstream input("input");

    std::string line;
    getline(input, line);
    Dir root;
    list_directory(input, line, root);
    input.close();

    size_t needed_space = 30000000 - (70000000 - get_Dir_size(root));

    size_t dir_to_be_disposed = 30000000;
    for(auto size : dir_sizes){
        if(size >= needed_space && size < dir_to_be_disposed){
            dir_to_be_disposed = size;
        }
    }
    std::cout << "answer: " << dir_to_be_disposed << std::endl;
}