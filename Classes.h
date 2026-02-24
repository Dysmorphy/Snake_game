#pragma once
#include <deque>
#include <random>

enum Field_consts {
    EMPTY,
    SNAKE_BODY,
    FOOD,
    WALL,
    SIZE = 20,
    BORDER_MAX = SIZE-1,
    BORDER_MIN = 0
    };
enum Directions {
    RIGHT,
    LEFT,
    UP,
    DOWN
};

struct Point {
    int row {};
    int col {};
    void print() const;
};

struct Field {
    int tiles [SIZE][SIZE];
    bool tiles_generated = false;
    void generate_field ();
    void print();
};
struct Snake {
    Point m_start {SIZE/2,SIZE/2};
    std::deque <Point> coords {{m_start}};
    void print() const;
    Point get_head () const {
        return coords.back();
    };
    Point get_tail () const {
        return coords.front();
    };
    
};
class FoodRandomizer {
    private:
    std::mt19937 mt {std::random_device {} ()};
    std::uniform_int_distribution <> in_frame {BORDER_MIN+1,BORDER_MAX-1};
    public:
    Point generate_position () {
        return {in_frame(mt),in_frame(mt)};
    };
};
class Game {
    private:
    Field game_field;
    Snake game_snake;
    FoodRandomizer randomizer;
    bool running = true;
    public:

    void start();
    bool is_collision (const Point& snake_head) const;
    Point make_move (int direction) const;
    void update_structure (int direction);
    void print();

};