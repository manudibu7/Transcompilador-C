#ifndef SYMBOL_H_
#define SYMBOL_H_

#include "parser.h"

typedef struct simbolo
{
    char *valor;
    struct simbolo *sig;
} simbolo_t;

simbolo_t *nuevo_simbolo(char *valor);

void borrar_simbolos(simbolo_t **lista);

void agregar_simbolo(simbolo_t **lista, simbolo_t *simbolo);

int contiene_simbolo(simbolo_t *lista, char *valor);

#endif 

