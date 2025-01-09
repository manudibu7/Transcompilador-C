#include "symbol.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct Simbolo {
    char *nombre;
    struct Simbolo *sig;
} Simbolo;

static Simbolo *tablaDeSimbolos = NULL;

bool agregarSimbolo(const char *nombre) {
    if (existeSimbolo(nombre)) {
        return false;
    }
    Simbolo *nuevoSimbolo = malloc(sizeof(Simbolo));
    nuevoSimbolo->nombre = strdup(nombre);
    nuevoSimbolo->sig = tablaDeSimbolos;
    tablaDeSimbolos = nuevoSimbolo;
    return true;
}

bool existeSimbolo(const char *nombre) {
    Simbolo *actual = tablaDeSimbolos;
    while (actual != NULL) {
        if (strcmp(actual->nombre, nombre) == 0) {
            return true;
        }
        actual = actual->sig;
    }
    return false;
}

void limpiarTabla() {
    Simbolo *actual = tablaDeSimbolos;
    while (actual != NULL) {
        Simbolo *aLiberar = actual;
        actual = actual->sig;
        free(aLiberar->nombre);
        free(aLiberar);
    }
    tablaDeSimbolos = NULL;
}

