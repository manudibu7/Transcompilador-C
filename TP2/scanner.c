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
    if (isalpha(c)) return 0; 
    if (isdigit(c)) return 1; 
    switch(c) {
        case '+': return 2;
        case '-': return 3;
        case '(': return 4;
        case ')': return 5;
        case ',': return 6;
        case ';': return 7;
        case ':': return 8;
        case '=': return 9;
        case '*': return 10;
        case '/': return 11;
        case '%': return 12;
        case '\0': return 13; 
        case ' ': case '\t': case '\n': case '\r': return 14; //blancos
        default: return 15; 
    }
}

Token obtener_token() {
    Token t;
    int estado = 0;
    char c;
    int i = 0;
    t.lexema[0] = '\0';

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
            t.lexema[i++] = c;
            t.lexema[i] = '\0';
            t.token = ERROR_GENERAL;
            return t;
        }

        int nuevo_estado = tabla_transicion[estado][col];

        if (nuevo_estado == 99) {
            t.lexema[i] = '\0';
            t.token = ERROR_GENERAL;
            return t;
        }

        if (nuevo_estado == 2 || nuevo_estado == 4) {
            t.lexema[i] = '\0';
             if (nuevo_estado == 2) {
                t.token = IDENTIFICADOR;
            } else {
                t.token = CONSTANTE;
            }
            if (c != EOF) {
                ungetc(c, stdin); 
            }
            return t;
        }

        if ((nuevo_estado >= 5 && nuevo_estado <= 10) || (nuevo_estado >= 15 && nuevo_estado <= 17)) {
            t.lexema[i++] = c;
            t.lexema[i] = '\0';
            switch (nuevo_estado) {
                case 5: t.token = MAS; break;
                case 6: t.token = MENOS; break;
                case 7: t.token = PARENTESIS_ABRE; break;
                case 8: t.token = PARENTESIS_CIERRA; break;
                case 9: t.token = COMA; break;
                case 10: t.token = PUNTO_Y_COMA; break;
                case 15: t.token = MULTIPLICACION; break;
                case 16: t.token = DIVISION; break;
                case 17: t.token = PORCENTAJE; break;
            }
            return t;
        }

        if (nuevo_estado == 11) {
            char next_char = fgetc(stdin);
            if (next_char == '=') {
                t.lexema[i++] = c;        
                t.lexema[i++] = next_char; 
                t.lexema[i] = '\0';
                t.token = ASIGNACION;
                return t;
            } else {
                if (next_char != EOF) ungetc(next_char, stdin);
                t.lexema[i++] = c; 
                t.lexema[i] = '\0';
                t.token = ERROR_FALTA_IGUAL;
                return t;
            }
        }

        if (nuevo_estado == 14) {
            t.lexema[i] = '\0';
            t.token = ERROR_FALTA_DOS_PUNTOS;
            return t;
        }

        t.lexema[i++] = c;
        estado = nuevo_estado;

        c = fgetc(stdin);
        if (c == EOF) {
            t.lexema[i] = '\0';
            t.token = FDT;
            return t;
        }
    }
}

const char* token_a_string(Token t) {
    static char buffer[256]; 
    buffer[0] = '\0'; 

    switch (t.token) {
        case IDENTIFICADOR:
            snprintf(buffer, sizeof(buffer), "Identificador '%s'", t.lexema);
            break;
        case CONSTANTE:
            snprintf(buffer, sizeof(buffer), "Constante '%s'", t.lexema);
            break;
        case MAS:
            snprintf(buffer, sizeof(buffer), "Mas '%s'", t.lexema);
            break;
        case MENOS:
            snprintf(buffer, sizeof(buffer), "Menos '%s'", t.lexema);
            break;
        case PARENTESIS_ABRE:
            snprintf(buffer, sizeof(buffer), "Parentesis que abre '%s'", t.lexema);
            break;
        case PARENTESIS_CIERRA:
            snprintf(buffer, sizeof(buffer), "Parentesis que cierra '%s'", t.lexema);
            break;
        case COMA:
            snprintf(buffer, sizeof(buffer), "Coma '%s'", t.lexema);
            break;
        case PUNTO_Y_COMA:
            snprintf(buffer, sizeof(buffer), "Punto y coma '%s'", t.lexema);
            break;
        case ASIGNACION:
            snprintf(buffer, sizeof(buffer), "Asignacion '%s'", t.lexema);
            break;
        case MULTIPLICACION:
            snprintf(buffer, sizeof(buffer), "Multiplicacion '%s'", t.lexema);
            break;
        case DIVISION:
            snprintf(buffer, sizeof(buffer), "Division '%s'", t.lexema);
            break;
        case PORCENTAJE:
            snprintf(buffer, sizeof(buffer), "Porcentaje '%s'", t.lexema);
            break;
        case FDT:
            snprintf(buffer, sizeof(buffer), "Fin de archivo '%s'", t.lexema);
            break;
        case ERROR_GENERAL:
            snprintf(buffer, sizeof(buffer), "Error general '%s'", t.lexema);
            break;
        case ERROR_FALTA_IGUAL:
            snprintf(buffer, sizeof(buffer), "Error: falta '=' despues de ':' '%s'", t.lexema);
            break;
        case ERROR_FALTA_DOS_PUNTOS:
            snprintf(buffer, sizeof(buffer), "Error: falta ':' antes de '=' '%s'", t.lexema);
            break;
        default:
            snprintf(buffer, sizeof(buffer), "Token desconocido '%s'", t.lexema);
            break;
    }

    return buffer;
}

