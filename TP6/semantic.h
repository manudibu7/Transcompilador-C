#ifndef SEMANTIC_H
#define SEMANTIC_H

#include <stdbool.h>

bool declararVariable(const char *nombre);
bool verificarVariableDeclarada(const char *nombre);
void generarAsignacion(const char *variable, const char *expresion);
void generarLectura(const char *variable);
void generarEscritura(const char *expresion);
char *generarVariableTemporal();
char *generarOperacionInfija(const char *izquierda, const char *operador, const char *derecha);

#endif
