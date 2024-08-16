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

void seleccionar_pieza(Pieza &pieza, int x, int y, bool &selec){        
    if(x == pieza.x && y == pieza.y){
        selec = !selec;
        pieza.seleccionada = !pieza.seleccionada;
    }else{
        if(pieza.seleccionada){
            switch (pieza.figura)
            {
            case 'T':
                if(pieza.x == x || pieza.y == y){ 
                    pieza.x = x;
                    pieza.y = y;
                }
                break;
            case 'A':
                if((pieza.x-x==pieza.y-y)||(y+x == pieza.x+pieza.y)){
                    pieza.x = x;
                    pieza.y = y;
                }
                break;
            case 'R':
                if((pieza.x == x || pieza.y == y)||(pieza.x-x==pieza.y-y)||(y+x == pieza.x+pieza.y)){
                    pieza.x = x;
                    pieza.y = y;
                }
                break;
            default:
                break;
            }
            pieza.seleccionada = false;
            selec = false;
        }
    }
}

bool deseleccionar_pieza(Pieza &pieza){
    if(pieza.seleccionada){
        pieza.seleccionada = false;
        return false;
        }
        return true;
}


int main() {

    initscr();
    keypad(stdscr, TRUE);
    Pieza torre;
    torre.x = 0; torre.y = 0; torre.figura = 'T';
    Pieza alfil;
    alfil.x = 1; alfil.y = 1; alfil.figura = 'A';
    Pieza reina;
    reina.x = 1; reina.y = 2; reina.figura = 'R';

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
                                    printw("+"); 
                                }else{
                                    if (alfil.seleccionada && k == 1 && l == 2 &&  ((alfil.x-j==alfil.y-i)||(i+j == alfil.x+alfil.y))){
                                    printw("+");
                                    }else{
                                        if (reina.seleccionada && k == 1 && l == 2 && (((reina.x-j==reina.y-i)||(i+j == reina.x+reina.y)) || (reina.y == i || reina.x == j))){
                                            printw("+");
                                        }else{
                                            dibujar_pieza(torre, i, j, l, k);
                                            dibujar_pieza(alfil, i, j, l, k);
                                            dibujar_pieza(reina, i, j, l, k);
                                            printw(" ");}
                                            }
                                        }
                            }
                        }
                    }
                }
            }

            //---------------RENDERIZADO DE LAS OPCIONES---------------//
            curs_set(1);
            attroff(A_REVERSE);
            move(25,0);
            printw("[ESC]     Para salir o deseleccionar una pieza.\n[FLECHAS] Para moverse.\n[ENTER]   Para seleccionar o mover una pieza.");
            key = getch();


            //---------------INPUT USUARIO---------------//
            switch (key)
            {
            case 27:
                if(seleccionando){
                    deseleccionar_pieza(torre);
                    deseleccionar_pieza(alfil);
                    deseleccionar_pieza(reina);
                }else{
                endwin();
                jugando = false;
                }
                seleccionando = false;
                clear();
                break;
            case 13: case 10:
                jugando = true;
                seleccionar_pieza(torre, posx, posy, seleccionando);
                seleccionar_pieza(alfil, posx, posy, seleccionando);
                seleccionar_pieza(reina, posx, posy, seleccionando);
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