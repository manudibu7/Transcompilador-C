#ifndef SCANNER_H
#define SCANNER_H

typedef enum {
    IDENTIFICADOR,
    CONSTANTE,
    PROGRAMA,
    FIN,
    LEER,
    ESCRIBIR,
    ENTERO,
    OPERADOR,
    ASIGNACION,
    CARACTER_PUNTUACION,
    MAS,
    MENOS,
    PARENTESIS_ABRE,
    PARENTESIS_CIERRA,
    COMA,
    PUNTO_Y_COMA,
    DOS_PUNTOS,
    IGUAL,
    MULTIPLICACION,
    DIVISION,
    PORCENTAJE,
    FDT,
    ERROR_GENERAL,
    ERROR_FALTA_IGUAL,
    ERROR_FALTA_DOS_PUNTOS
} t_token;

typedef struct {
    t_token token;         
    char lexema[100];  
} Token;

Token obtener_token();
const char* token_a_string(Token token);

#endif
