#include <iostream>
#include <deque>
#include <stdexcept>


enum Field_consts {
    EMPTY,
    SNAKE_BODY,
    FOOD,
    WALL,
    RIGHT,
    LEFT,
    UP,
    DOWN,
    SIZE = 20,
    BORDER_MAX = SIZE-1,
    BORDER_MIN = 0
    };

struct Point {
    int row;
    int col;
    void print() const {
        std::cout<<row<<" "<<col;
    }
};

struct Field{
    int tiles [SIZE][SIZE];
    bool tiles_generated = false;
    void generate (){
    for (int row =0;row<SIZE;row++){
        for (int col = 0;col<SIZE;col++){
            if (row == BORDER_MIN || col == BORDER_MIN || row == BORDER_MAX || col == BORDER_MAX){
                tiles [row][col] = WALL;
                }
            else tiles [row][col] = EMPTY;
            }
        }
        tiles_generated = true;
    }
};

struct Snake {
    Point m_start {SIZE/2,SIZE/2};
    std::deque <Point> coords {{m_start}};
    void print() const{
        for (int el = 0;el<coords.size();el++){
            std::cout<<coords[el].row<<" "<<coords[el].col;
        }
        std::cout<<std::endl;
    }
    Point get_head () const{
        return coords [coords.size()-1];
    }
    Point get_tail () const {
        return coords [0];
    }
};
class Game {
    private:
    Field game_field;
    Snake game_snake;
    bool running = true;
    public:
    void start(){
        game_field.generate();
    }
    bool check_move() const {
        Point snake_head = game_snake.get_head();
        if (snake_head.row == BORDER_MIN 
            || snake_head.row == BORDER_MAX 
            || snake_head.col == BORDER_MIN 
            || snake_head.col == BORDER_MAX) return true;
        return false;
    }
    Point make_move (int direction){
        Point snake_head = game_snake.get_head();
        switch (direction) {
        case RIGHT:
            return {snake_head.row,snake_head.col+1};
            break;
        case LEFT:
            return {snake_head.row,snake_head.col-1};
            break;
        case UP:
            return {snake_head.row-1,snake_head.col};
            break;
        default:
            return {snake_head.row+1,snake_head.col};
            break;
        } 
    }
    void update_structure (int direction){
        if (game_field.tiles_generated == false) {
            throw std::logic_error("The field hasn't been generated");
        }
        Point new_head = make_move(direction);
        if (check_move ()){
            running = false;
            return;
        }
        bool ate_food = false;
        if (game_field.tiles[new_head.row][new_head.col] == FOOD){
            ate_food = true;
        }
        if (ate_food == false){
            Point tail = game_snake.get_tail();
            game_field.tiles[tail.row][tail.col] = EMPTY;
            game_snake.coords.pop_front();
        }
        game_field.tiles[new_head.row][new_head.col] = SNAKE_BODY;
        game_snake.coords.push_back(new_head);
        
    }

};