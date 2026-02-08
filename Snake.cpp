#include <iostream>
#include <deque>
#include <stdexcept>
#include <random>

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
    int row {};
    int col {};

    void print() const {
        std::cout<<row<<" "<<col;
    //need overloaded = and std::cout operators
    //once completed, change check_existence method
    //need to write tests for the existing classes and member functions
    // Implement randomizer into update_structure member function
    }
};

struct Field{
    int tiles [SIZE][SIZE];
    bool tiles_generated = false;
    void generate_field (){
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
    friend void print(const Field& object){
        for (int row = 0;row<SIZE;row++){
            for (int col =0;col<SIZE;col++){
                std::cout<<object.tiles[row][col]<<" ";
            }
            std::cout<<'\n';
        }
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

    bool check_existence (Point el) {
        for (int index=0;index<coords.size();index++){
            if (el.row == coords[index].row && el.col == coords[index].col){
                return true;
            }
        }
        return false;
    }

};
class FoodRandomizer {
    private:
    std::mt19937 mt {std::random_device {} ()};
    std::uniform_int_distribution<> in_frame {BORDER_MIN+1,BORDER_MAX-1};

    public:
    Point generate_position(){
        return {in_frame(mt),in_frame(mt)};
    }
};
class Game {
    private:

    Field game_field;
    Snake game_snake;
    FoodRandomizer randomizer;
    bool running = true;

    public:

    void start(){
        game_field.generate_field();
        Point snake = game_snake.get_head();
        game_field.tiles[snake.row][snake.col] = SNAKE_BODY;
    }

    bool check_move(const Point& snake_head) const {
        if (snake_head.row == BORDER_MIN 
            || snake_head.row == BORDER_MAX 
            || snake_head.col == BORDER_MIN 
            || snake_head.col == BORDER_MAX 
            || game_field.tiles[snake_head.row][snake_head.col] == SNAKE_BODY) return true;
        return false;
    }

    Point make_move (int direction) const{
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
        if (check_move (new_head)){
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

    friend void print(const Game& object);

    //delete
    void make_food (const Point& tile){
        game_field.tiles[tile.row][tile.col] = FOOD;
    }

};

void print(const Game& object){
    print(object.game_field);
}


int main(){
        Game a {};
        a.start();
        print(a);
}