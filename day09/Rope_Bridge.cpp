#include <iostream>
#include <fstream>
#include <vector>
#include <set>

#define RIGHT 'R'
#define LEFT 'L'
#define UP 'U'
#define DOWN 'D'

typedef struct coord {
    coord() : x(0), y(0) {};
    coord(int x, int y) : x(x), y(y) {}

    bool operator < (coord const& rhs) const{
        return this->x < rhs.x || (this->x == rhs.x && this->y < rhs.y);
    }

    int x;
    int y;
} coord;

void calculate_tail_pos(coord &head, coord &tail){
    if(head.x - tail.x == 2){
        tail.x++;
        tail.y = head.y;
    } else if(head.x - tail.x == -2){
        tail.x--;
        tail.y = head.y;
    } else if(head.y - tail.y == 2){
        tail.y++;
        tail.x = head.x;
    } else if(head.y - tail.y == -2){
        tail.y--;
        tail.x = head.x;
    }
}

int main(){
    std::ifstream input("input");
    std::set<coord> visited;

    coord head;
    coord tail;
    char direction;
    int steps;
    do{
        input >> direction;
        input >> steps;

        for(;steps > 0; steps--){
            if(direction == RIGHT){
                head.x += 1;
            } else if(direction == LEFT){
                head.x -= 1;
            } else if(direction == UP){
                head.y += 1;
            } else if(direction == DOWN){
                head.y -= 1;
            }
            calculate_tail_pos(head, tail);
            visited.emplace(tail.x, tail.y);
        }
    } while(!input.eof());
    input.close();

    std::cout << "amount of places visited " << visited.size() << std::endl;
}