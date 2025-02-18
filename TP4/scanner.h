#ifndef SCANNER_H
#define SCANNER_H

#include <stdio.h>

typedef enum {
    PROGRAMA,
    FIN,
    ENTERO,
    LEER,
    ESCRIBIR,
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
    FDT,  
    ERROR_GENERAL,
    ERROR_FALTA_IGUAL,      // erorr: se leyo :' pero no le sigue =
    ERROR_FALTA_DOS_PUNTOS,   // error: se leyo '=' sin haber venido':
    ERROR_IDENTIFICADOR,
    ERROR_CONSTANTE
} t_token;

typedef struct {
    t_token token;         
    char lexema[100];  
    int linea;            
    int columna;          
} Token;

Token obtener_token();
const char* token_a_string(Token token);

#endif
