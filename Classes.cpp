#include "Consts.h"
#include "Classes.h"
#include <iostream>


void Point::print() const { 
    std::cout<<row<<" "<<col<<"\n";
};


void Field::generate_field(){
    for (int row =0;row<SIZE;row++){
        for (int col = 0;col<SIZE;col++){
            if (row == BORDER_MIN || col == BORDER_MIN || row == BORDER_MAX || col == BORDER_MAX){
                tiles [row][col] = WALL;
                }
            else tiles [row][col] = EMPTY;
            }
        }
        tiles_generated = true;
};

void Field::print() {
    for (int row = 0;row<SIZE;row++){
            for (int col =0;col<SIZE;col++){
                std::cout<<tiles[row][col]<<" ";
            }
            std::cout<<'\n';
        }
}

void Game::start () {
    game_field.generate_field();
    Point snake = game_snake.get_head();
    game_field.tiles[snake.row][snake.col] = SNAKE_BODY;
};


bool Game::is_collision (const Point& snake_head) const {
    if (snake_head.row == BORDER_MIN 
            || snake_head.row == BORDER_MAX 
            || snake_head.col == BORDER_MIN 
            || snake_head.col == BORDER_MAX 
            || game_field.tiles[snake_head.row][snake_head.col] == SNAKE_BODY) return true;
        return false;
};


Point Game::make_move (int direction) const{
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
};


void Game::update_structure (int direction) {
    if (game_field.tiles_generated == false) {
            throw std::logic_error("The field hasn't been generated");
        }
        Point new_head = make_move(direction);
        if (is_collision (new_head)){
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
};
void Game::print(){
    game_field.print();
}



