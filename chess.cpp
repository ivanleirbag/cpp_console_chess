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
bool hover = false;

struct Pieza{
    int x;
    int y;
    bool seleccionada = false;
    char figura;
};

void dibujar_pieza(Pieza pieza, int ty, int tx, int by, int bx){
    if(pieza.x == tx && pieza.y == ty && bx == 1 && by == 2){
        printw("%c", pieza.figura);
    }
}

int main() {

    initscr();
    keypad(stdscr, TRUE);
    Pieza torre;
    torre.x = 0; torre.y = 0; torre.figura = 'T';

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

            //---------------RENDERIZADO DEL TABLERO---------------//
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
                            if (posy == i && posx == j && k%2 == 0 && l%2 != 0){           //dibuja las esquinas del selector
                                if(hover){printw("+");}else{printw("-");}
                            }else{
                            if (hover && k == 1 && l == 2 && (posy == i || posx == j)){    //sino, dibuja espacios vacíos
                                printw("."); 
                            }else{
                            dibujar_pieza(torre, i, j, l, k);
                            printw(" ");
                            }}
                        }
                    }
                }
            }

            /*move((1+(posy*3)),(2+(posx*5)));
            printw("%c", torre.figura);
            */
            curs_set(1);
            attroff(A_REVERSE);
            move(25,0);
            printw("[ESC] Para salir.\n[FLECHAS] Para moverse.\n[ENTER] Para seleccionar una pieza.");
            key = getch();


            //---------------INPUT USUARIO---------------//
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
            case 13: case 10:
                jugando = true;
                hover = !hover;
                clear();
                break;
            case KEY_LEFT:
                if (posx > 0){posx -= 1;}
                break;
            case KEY_RIGHT:
                if (posx<7){posx += 1;}
                break;
            case KEY_UP:
                if (posy > 0){posy -= 1;}
                break;
            case KEY_DOWN:
                if (posy<7){posy += 1;}
                break;
            default:
                break;
            }
        }
    }
    return 0;
}