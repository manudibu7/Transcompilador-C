#ifndef SCANNER_H
#define SCANNER_H

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

#endif // SCANNER_H


