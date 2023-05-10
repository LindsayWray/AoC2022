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
        if(head.y > tail.y){
            tail.y++;
        } else if (head.y < tail.y){
            tail.y--;
        }
    } else if(head.x - tail.x == -2){
        tail.x--;
        if(head.y > tail.y){
            tail.y++;
        } else if (head.y < tail.y){
            tail.y--;
        }
    } else if(head.y - tail.y == 2){
        tail.y++;
        if(head.x > tail.x){
            tail.x++;
        } else if (head.x < tail.x){
            tail.x--;
        }
    } else if(head.y - tail.y == -2){
        tail.y--;
        if(head.x > tail.x){
            tail.x++;
        } else if (head.x < tail.x){
            tail.x--;
        }
    }
}

int main(){
    std::ifstream input("input");
    std::set<coord> visited;
    std::vector<coord> snake(10);

    char direction;
    int steps;
    do{
        input >> direction;
        input >> steps;

        for(;steps > 0; steps--){
            if(direction == RIGHT){
                snake.front().x += 1;
            } else if(direction == LEFT){
                snake.front().x -= 1;
            } else if(direction == UP) {
                snake.front().y += 1;
            } else if(direction == DOWN) {
                snake.front().y -= 1;
            }
            for(int i = 1; i < snake.size(); i++){
                calculate_tail_pos(snake[i - 1], snake[i]);
            }
            visited.emplace(snake.back().x, snake.back().y);
        }
    } while(!input.eof());
    input.close();

    std::cout << "amount of places visited " << visited.size() << std::endl;
}