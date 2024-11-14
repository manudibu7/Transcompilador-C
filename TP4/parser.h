#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>
#include "scanner.h"
#include <string.h>
#include <stdbool.h>


void parser();
void programa();
void sentencia();
void expresion();
void termino();
void primaria();
void listaExpresiones();
void listaIdentificadores();
void obtenerProximoToken();
void listaSentencias();
void match(t_token token_esperado);

Token tokenActual;
t_token token;







#endif