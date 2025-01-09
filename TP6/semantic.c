#include "semantic.h"
#include "symbol.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int contadorTemporales = 1;

bool declararVariable(const char *nombre) {
    if (!agregarSimbolo(nombre)) {
        fprintf(stderr, "// Error semántico: La variable '%s' ya está declarada\n", nombre);
        return true;
    }
    printf("int %s;\n", nombre);
    return false;
}

bool verificarVariableDeclarada(const char *nombre) {
    if (!existeSimbolo(nombre)) {
        fprintf(stderr, "// Error semántico: La variable '%s' no está declarada\n", nombre);
        return true;
    }
    return false;
}

void generarAsignacion(const char *variable, const char *expresion) {
    printf("%s = %s;\n", variable, expresion);
}

void generarLectura(const char *variable) {
    printf("scanf(\"%%d\", &%s);\n", variable);
}

void generarEscritura(const char *expresion) {
    printf("printf(\"%%d\\n\", %s);\n", expresion);
}

char *generarVariableTemporal() {
    char *nombreTemporal = malloc(20);
    if (!nombreTemporal) {
        fprintf(stderr, "// Error: No se pudo asignar memoria para una variable temporal\n");
        exit(EXIT_FAILURE);
    }
    snprintf(nombreTemporal, 20, "_Temp%d", contadorTemporales++);
    printf("int %s;\n", nombreTemporal);
    return nombreTemporal;
}

char *generarOperacionInfija(const char *izquierda, const char *operador, const char *derecha) {
    char *temporal = generarVariableTemporal();
    printf("%s = %s %s %s;\n", temporal, izquierda, operador, derecha);
    return temporal;
}


