#include <ncurses.h>
#include <iostream>
#include <string.h>

int main(void){
    int i, j;
    const int casilleroy = 3;
    const int casillerox = 5;
    const int tablero = 8;


    initscr();
    start_color();

    for (i = 1; i <= tablero; i++){
        for (j = 1; j <=tablero; j++){
            if ((i+j)%2 == 0){
                attron(A_REVERSE);
            }else{
                attroff(A_REVERSE);
            }
            for (int k = 0; k < casilleroy; k++){
                for (int w = 0; w < casillerox; w++){
                    printw(" ");}
                printw("\n");
            }
        }
        printw("\n");
    }

    refresh();
    getch();
    endwin();

    return 0;
}