#include "Classes.h"
#include <iostream>
#include <ncurses.h>


int main(){
        Game game {};
        game.start();

        initscr();
        curs_set(0);
        noecho();
        keypad(stdscr, true);
        nodelay(stdscr, true);
        
        game.draw_borders();
        game.draw_inner();

        int direction = UP;

        while (game.running == true){
                int button_pressed = getch();
                
                switch (button_pressed) {

                        case KEY_UP:
                        direction = UP;
                        break;

                        case KEY_DOWN:
                        direction = DOWN;
                        break;

                        case KEY_RIGHT:
                        direction = RIGHT;
                        break;
                        
                        case KEY_LEFT:
                        direction = LEFT;
                        break;

                }

                game.update_structure(direction);

                game.draw_inner();

                napms(100);

        
        }
        
        endwin();
        
        
}