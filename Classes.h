#pragma once
#include <deque>
#include <random>

enum Field_consts {
    EMPTY,
    SNAKE_BODY,
    FOOD,
    WALL,
    SIZE = 16,
    BORDER_MAX = SIZE-1,
    BORDER_MIN = 0,
    NON_EXISTENT = -1
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
    friend inline std::ostream& operator<<(std::ostream& out,const Field& field);
};
inline std::ostream& operator<<(std::ostream& out, const Field& field);


struct Snake {
    Point m_start {SIZE/2,SIZE/2};
    std::deque <Point> coords {{m_start}};
    Point prev_tail{NON_EXISTENT,NON_EXISTENT};

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
    Point make_move (int direction) const;
    Point last_food_generated {NON_EXISTENT,NON_EXISTENT};

    public:
    bool running = true;

    void start();
    bool is_collision (const Point& snake_head) const;
    void update_structure (int direction);
    friend std::ostream& operator<< (std::ostream& out, const Game& game);

    void test_add_food(const Point& food_coords){
        game_field.tiles[food_coords.row][food_coords.col] = FOOD;
    }

    void draw_borders () const;
    void draw_inner () const;

};
std::ostream& operator<< (std::ostream& out, const Game& game);