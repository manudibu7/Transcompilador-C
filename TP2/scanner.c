#include "scanner.h"
//                                      L   D   +   -   (    )  ,   ;    :  =   fdt esp otro
int T[NUM_ESTADOS][NUM_CARACTER]       {1 , 3,  5,  6,  7,  8,  9,  10, 11, 14, 13, 0, 14
                                        1 , 1,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2         /**/
                                        99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99
                                        4,  3,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4
                                        99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99
                                        99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99
                                        99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99
                                        99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99
                                        99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99
                                        99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99
                                        99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99
                                        14, 14, 14, 14, 14, 14, 14, 14, 14, 12, 14, 14, 14
                                        99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99
                                        99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99
                                        99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99};   //FALTA AGREGAR LOS ESTADOS DE * , / , % 

Token scanner(){
    int estado = 0;
    char caracter;

    while (!debo_parar(estado)) {
        caracter = getchar();
        estado = T[estado][mapear_caracter(caracter)];
        // Acciones como construir el lexema, contar líneas, etc.
    }

    if (aceptor(estado)) {
        if (centinela(estado)) {
            ungetc(caracter, stdin);  // Si el estado es centinela, devolvemos el caracter
        }
        return aceptar(estado, lexema);
    } else {
        return error(estado, lexema);
    }
}




