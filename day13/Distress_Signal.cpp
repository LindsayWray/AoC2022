#include <iostream>
#include <fstream>
#include <vector>

typedef struct packet {
    std::string left;
    std::string right;
} packet;

std::vector<std::string> tokenize(std::string str) {
    std::vector<std::string> parts;

    int level = 0;
    int startIndex = 1; // skip opening [
    for(int i = 1; i < str.length(); i++) {
        if (str[i] == '[') {
            level++;
        }
        if (str[i] == ']') {
            level--;
            if (i == str.length() - 1) {
                parts.push_back(str.substr(startIndex, i - startIndex));
            }
        }
        if (str[i] == ',' && level == 0) {
            parts.push_back(str.substr(startIndex, i - startIndex));
            startIndex = i + 1;
        }
    }    
    return parts;
}

int compare(std::string left, std::string right);

int compareInts(int left, int right) {
    if (left < right) {
        return -1;
    } else if (left > right) {
        return 1;
    }
    return 0;
}

int compareLists(std::vector<std::string> left, std::vector<std::string> right) {
    for(int i = 0; i < left.size(); i++) {
        if (i >= right.size()) {
            return 1;
        }
        auto c = compare(left[i], right[i]);
        if (c != 0) {
            return c;
        }
    }
    if (left.size() < right.size()) {
        return -1;
    }
    return 0;
}


int compare(std::string left, std::string right) {
    if (left.empty()) {
        return -1;
    }
    if (right.empty()) {
        return 1;
    }
    if (left[0] == '[' && right[0] == '[') {
        return compareLists(tokenize(left), tokenize(right));
    } else if (left[0] != '[' && right[0] != '[') {
        return compareInts(std::stoi(left), std::stoi(right));
    } else {
        if (left[0] == '[') {
            return compareLists(tokenize(left), std::vector<std::string>(1, right));
        } else {
            return compareLists(std::vector<std::string>(1, left), tokenize(right));
        }
    }
}

bool inOrder(packet& p) {
    auto ltokens = tokenize(p.left);
    auto rtokens = tokenize(p.right);

    return compare(p.left, p.right) == -1;
}

int main(){
    std::ifstream input("input");

    std::vector<packet> packets;

    std::string line;
    do{
        packet p;
        input >> p.left;
        input >> p.right;
        packets.push_back(p);
    }while (!input.eof());
    input.close();

    int answer = 0;
    for (int i = 0; i < packets.size(); i++){
        if (inOrder(packets[i])) {
            std::cout << "Index " << i + 1 << " is in order" << std::endl;
            answer += (i + 1);
        }
    }
    
    std::cout << "Final score: " << answer << std::endl;
}