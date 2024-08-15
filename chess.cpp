#include <ncurses.h>
#include <iostream>
#include <string.h>

#include <ncurses.h>

void options(int key_pressed){
    switch (key_pressed)
    {
    case 27:
        endwin();
        break;
    default:
        break;
    }
}



int main() {
    
    int i, j, k, l, key;
    const int tablero = 8;
    bool running = true;

    initscr();


    while(running){
        key = getch();
        refresh();
        options(key);

        for(i = 0; i < tablero; i++) {
            for(j = 0; j < tablero; j++) {
                if((i+j) % 2 == 0) {
                    attron(A_REVERSE);
                } else {
                    attroff(A_REVERSE);
                }
                for(k = 0; k < 3; k++) {
                    move((3*i)+k, 5*j);
                    for(l = 0; l < 5; l++) {
                        printw(" ");
                    }
                }
            }
        }
        printw("\n");
    }
    return 0;
}