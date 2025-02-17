#ifndef SCANNER_H
#define SCANNER_H

#include <stdio.h>  // Para manejar la entrada/salida estándar

// Definición de los posibles tokens que el escáner puede devolver
typedef enum {
    IDENTIFICADOR,
    CONSTANTE,
    MAS,
    MENOS,
    PARENTESIS_ABRE,
    PARENTESIS_CIERRA,
    COMA,
    PUNTO_Y_COMA,
    ASIGNACION,
    MULTIPLICACION,
    DIVISION,
    PORCENTAJE,
    FDT,                     // Fin de archivo
    ERROR_GENERAL,           // Error de carácter no válido
    ERROR_FALTA_IGUAL,      // Error de falta de '=' para asignación
    ERROR_FALTA_DOS_PUNTOS, // Error de falta de ':' para asignación
    ERROR_IDENTIFICADOR,    // Error de identificador (contiene caracteres no válidos)
    ERROR_CONSTANTE,        // Error en constante (números seguidos de letras)
} t_token;

// Estructura para representar un token, su lexema y la línea/columna de aparición
typedef struct {
    t_token token;         
    char lexema[100];  
    int linea;            // Número de línea del token
    int columna;          // Número de columna del token
} Token;

// Función para obtener el siguiente token
Token obtener_token();

// Función para convertir un token a su representación en cadena
const char* token_a_string(Token token);




// Función auxiliar para verificar si un identificador es válido
int es_error_identificador(const char* lexema);

// Función auxiliar para verificar si una constante es válida
int es_error_constante(const char* lexema);

#endif

