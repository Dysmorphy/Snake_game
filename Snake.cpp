#include <iostream>
#include <deque>


struct Point {
    int row;
    int col;
    void print(){
        std::cout<<row<<" "<<col;
    }
};

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

void print_arr (const int arr[SIZE][SIZE]){
    int size = 20;
    for (int x = 0;x<size;x++){
        for (int y= 0;y<size;y++){
            std::cout<<arr[x][y];
        }
        std::cout<<"\n";
    }
}
void print_vec (const std::deque<Point>& vec){
    for (int el=0;el<vec.size();el++){
        std::cout<<vec[el].row<<" "<<vec[el].col<<'\n';
    }
}
bool move_check (const Point& snake_head){
    //checking, whether snake has reached the border of the field
    return snake_head.row == BORDER_MIN 
    || snake_head.row == BORDER_MAX 
    || snake_head.col == BORDER_MIN 
    || snake_head.col == BORDER_MAX;
}
Point make_move(const std::deque <Point>& snake_coords,int direction) {
    //making a move using a given direction
    Point snake_head = snake_coords[snake_coords.size()-1];
    switch (direction) {
        case RIGHT:
            return {snake_head.row,++snake_head.col};
            break;
        case LEFT:
            return {snake_head.row,--snake_head.col};
            break;
        case UP:
            return {--snake_head.row,snake_head.col};
            break;
        default:
            return {++snake_head.row,snake_head.col};
            break;
    }
}
void update_structure (int field[SIZE][SIZE],std::deque <Point>& snake_coords, Point head_new){
    //updating a snake and a field after the snaked has moved
    bool ate_food = (field[head_new.row][head_new.col] == FOOD);
    if (ate_food == false) {
        Point deleted_coord = snake_coords[0];
        field [deleted_coord.row][deleted_coord.col] = EMPTY;
        snake_coords.pop_front();
        
    }
    snake_coords.push_back(head_new);
    field [head_new.row][head_new.col] = SNAKE_BODY;
}


int main(){
    //creating a field for a snake
    int field [SIZE][SIZE];

    for (int row =0;row<SIZE;row++){
        for (int col = 0;col<SIZE;col++){
            if (row == BORDER_MIN || col == BORDER_MIN || row == BORDER_MAX || col == BORDER_MAX){
                field [row][col] = WALL;
            }
            else field [row][col] = EMPTY;
        }
    }

    //creating a snake
    std::deque <Point> snake_coords;
    Point snake_start = {SIZE/2,SIZE/2};
    snake_coords.push_back(snake_start);
    
    
}