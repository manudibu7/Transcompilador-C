#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>
#include "scanner.h"
#include <stdbool.h>
#include <string.h>


void parser();
void sentencia();
void expresion();
void termino();
void primaria();
void listaExpresiones();
void listaIdentificadores();
void listaSentencias();
void match(t_token token_esperado);
void obtenerProximoToken();


extern Token tokenActual;
extern t_token token;

#endif
