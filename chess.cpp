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
bool seleccionando = false;

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

void seleccionar_pieza(Pieza &pieza, int &x, int &y, bool &selec){
    if(x == pieza.x && y == pieza.y){
        selec = !selec;
        pieza.seleccionada = !pieza.seleccionada;
    }else{
        if(pieza.seleccionada){
            pieza.x = x;
            pieza.y = y;
            selec = !selec;
            pieza.seleccionada = !pieza.seleccionada;
        }
    }
}
void deseleccionar_pieza(Pieza &pieza, bool &selec){
    if(selec && pieza.seleccionada){
        selec = false;
        pieza.seleccionada = false;
    }
}

int main() {

    initscr();
    keypad(stdscr, TRUE);
    Pieza torre;
    torre.x = 0; torre.y = 0; torre.figura = 'T';
    Pieza alfil;
    alfil.x = 1; alfil.y = 1; alfil.figura = 'A';

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
                                if(seleccionando){printw("+");}else{printw("-");}
                            }else{
                            if (torre.seleccionada && k == 1 && l == 2 && (torre.y == i || torre.x == j)){  
                                printw("."); 
                            }else{
                            if (alfil.seleccionada && k == 1 && l == 2 && ((alfil.y+i == alfil.x+j)||(i+j == tablero))){
                                printw(".");
                            }else{
                                dibujar_pieza(torre, i, j, l, k);
                                dibujar_pieza(alfil, i, j, l, k);
                                printw(" ");
                            }}}
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
            case 27:
                if(seleccionando && torre.seleccionada){
                    seleccionando = false;
                    torre.seleccionada = false;
                }else{
                endwin();
                jugando = false;
                }
                clear();
                break;
            case 13: case 10:
                jugando = true;
                seleccionar_pieza(torre, posx, posy, seleccionando);
                seleccionar_pieza(alfil, posx, posy, seleccionando);
                clear();
                break;
            case KEY_LEFT:
                if(torre.seleccionada && posx > 0){
                    if(posy == torre.y){posx-=1;}else{break;}
                }else{
                    if (posx > 0){posx -= 1;}}
                break;
            case KEY_RIGHT:
                if(torre.seleccionada && posx<7){
                    if(posy == torre.y){posx+=1;}else{break;}
                }else{
                    if (posx<7){posx += 1;}}
                break;
            case KEY_UP:
                if(torre.seleccionada && posy > 0){
                    if(posx == torre.x){posy-=1;}else{break;}
                }else{
                    if (posy > 0){posy -= 1;}}
                break;
            case KEY_DOWN:
                if(torre.seleccionada && posy<7){
                    if(posx == torre.x){posy+=1;}else{break;}
                }else{
                    if (posy<7){posy += 1;}}
                break;
            default:
                break;
            }
        }
    }
    return 0;
}