#include "scanner.h"
#include <stdio.h>
#include <ctype.h>
#include <string.h>

int tabla_transicion[19][16] =  {
    // L   D   +   -   (   )   ,   ;   :   =   *   /   %   fdt esp otro
    {  1,  3,  5,  6,  7,  8,  9, 10, 11, 14, 15, 16, 17, 13,  0, 14},  // 0-
    {  1,  1,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2},  // 1
    { 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99},  // 2+
    {  4,  3,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4},  // 3
    { 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99},  // 4+
    { 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99},  // 5+
    { 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99},  // 6+
    { 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99},  // 7+
    { 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99},  // 8+
    { 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99},  // 9+
    { 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99},  // 10+
    { 14, 14, 14, 14, 14, 14, 14, 14, 14, 12, 14, 14, 14, 14, 14, 14},  // 11
    { 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99},  // 12+
    { 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99},  // 13+
    { 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99},  // 14+
    { 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99},  // 15+
    { 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99},  // 16+
    { 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99},  // 17+
    { 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99}   // 18+
};

int obtener_columna(char c) {
    if (isalpha(c)) return 0;  // Letras
    if (isdigit(c)) return 1;  // Dígitos
    if (c == '+') return 2;
    if (c == '-') return 3;
    if (c == '(') return 4;
    if (c == ')') return 5;
    if (c == ',') return 6;
    if (c == ';') return 7;
    if (c == ':') return 8;
    if (c == '=') return 9;
    if (c == '*') return 10;
    if (c == '/') return 11;
    if (c == '%') return 12;
    if (c == EOF) return 13;
    if (isspace(c)) return 14;
    return 15;  // Otro (caracter inválido)
}



Token obtener_token() {
    Token t;
    int estado = 0;
    char c;
    int i = 0;
    t.lexema[0] = '\0';
    char errores[100] = "";
    int errorIndex = 0;

    do {
        c = fgetc(stdin);
        if (c == EOF) {
            t.token = FDT;
            t.lexema[0] = '\0';
            return t;
        }
    } while (isspace(c));

    while (1) {
        int col = obtener_columna(c);
        if (col == 15) {
            errores[errorIndex++] = c;
            errores[errorIndex] = '\0';
        } else {
            if (errorIndex > 0) {
                strcpy(t.lexema, errores);
                t.token = ERROR_GENERAL;
                return t;
            }
            t.lexema[i++] = c;
            t.lexema[i] = '\0';
        }
        c = fgetc(stdin);
        if (c == EOF) break;
    }
    return t;
}

