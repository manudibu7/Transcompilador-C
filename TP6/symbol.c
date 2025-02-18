#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "symbol.h"

simbolo_t *nuevo_simbolo(char *valor)
{
    simbolo_t *simbolo = malloc(sizeof(simbolo_t));
    simbolo->valor = malloc(sizeof(char) * (strlen(valor) + 1));
    strcpy(simbolo->valor, valor);
    simbolo->sig = NULL;
    return simbolo;
}

void agregar_simbolo(simbolo_t **lista, simbolo_t *simbolo)
{
    simbolo->sig = *lista;
    *lista = simbolo;
}

void borrar_simbolos(simbolo_t **lista)
{
    simbolo_t *actual = *lista;
    simbolo_t *sig;

    while (actual != NULL)
    {
        sig = actual->sig;
        free(actual);
        actual = sig;
    }

    *lista = NULL;
}

int contiene_simbolo(simbolo_t *lista, char *valor)
{
    simbolo_t *aux;

    for (aux = lista; aux != NULL; aux = aux->sig)
    {
        if (strcmp(aux->valor, valor) == 0)
            return 0;
    }
    return -1;
}