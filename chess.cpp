#include <ncurses.h>
#include <iostream>
#include <string.h>

#include <ncurses.h>

int main() {
    
    int i, j, k, l, key;
    const int tablero = 8;
    bool menu = true;
    bool jugando = false;

    initscr();
    curs_set(0);
    keypad(stdscr, TRUE);

    while(menu){
        attroff(A_REVERSE);
        clear();
        refresh();
        printw("Presiona [ENTER] para comenzar a jugar");
        refresh();

        key = getch();
        switch (key)
        {
        case 27:
            endwin();
            menu = false;
            break;
        case 13:
            jugando = true;
            clear();
            break;
        case 10:
            jugando = true;
            clear();
            break;
        default:
            break;
        }

        while(jugando){

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

            move(1,2);
            printw("0");
            
            

            key = getch();
            switch (key)
            {
            case 27:
                endwin();
                jugando = false;
                break;
            case 13:
                jugando = true;
                clear();
                break;
            case 10:
                jugando = true;
                clear();
                break;
            default:
                break;
            }

        }
    }
    return 0;
}