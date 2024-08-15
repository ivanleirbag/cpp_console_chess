#include <ncurses.h>
#include <iostream>
#include <string.h>

#include <ncurses.h>

int i, j, k, l, key;
int posx = 0;
int posy = 0;

const int tablero = 8;
bool menu = true;
bool jugando = false;

typedef struct
{
    int x;
    int y;
    bool seleccionada = false;
    char figura;
}Pieza;
Pieza torre;
torre.x = 0;
torre.y = 0;
torre.figura = 'T';

int main() {

    initscr();
    keypad(stdscr, TRUE);

    while(menu){
        attroff(A_REVERSE);
        curs_set(0);
        clear();
        refresh();
        printw("> Presiona [ENTER] para comenzar a jugar.\n\n");
        printw("> Presiona [ESC] para cerrar el programa.");
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
                            if (k == 1 && l == 2 && (posy == i || posx == j)){
                                printw(".");
                            }else{
                            printw(" ");
                            }
                        }
                    }
                }
            }
            move((1+(posy*3)),(2+(posx*5)));
            printw("%c", torre.figura);
            attroff(A_REVERSE);
            curs_set(1);
            move(25,0);
            printw("[ESC] Para salir.\n[FLECHAS] Para moverse.\n[ENTER] Para seleccionar una pieza.");
            key = getch();

            switch (key)
            {
            case 49: case 50: case 51: case 52:
            case 53: case 54: case 55: case 56:
                posx = key-49;
                posy = key-49;
                break;

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
            case KEY_LEFT:
                if (posx > 0){
                posx -= 1;}
                break;
            case KEY_RIGHT:
                if (posx<7){posx += 1;}
                break;
            case KEY_UP:
                if (posy > 0){
                    posy -= 1;}
                break;
            case KEY_DOWN:
                if (posy<7){
                    posy += 1;}
                break;
            default:
                break;
            }
        }
    }
    return 0;
}