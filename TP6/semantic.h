#ifndef SEMANTIC_H_
#define SEMANTIC_H_

#include "parser.h"
#include "symbol.h"
// #include "main.c"

void inicializar(char *nom_programa);

void finalizar(void);

int declarar(char *identificador);

int declarado(char *identificador);

void asignar(char *id, char *expr);

void leer(char *id);

void escribir(char *expr);

char *operar(char *opIzq, char op, char *opDer);


char *negar(char *expr);

#endif
