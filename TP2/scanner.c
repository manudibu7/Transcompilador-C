#include "scanner.h"
#include <stdio.h>
#include <ctype.h>
#include <string.h>

int tabla_transicion[18][16] =  {
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
    { 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99}   // 17+
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
        case ' ': return 14; 
        default: return 99;   
    }
}

Token obtener_token(){
    Token t;
    int estado = 0;
    char c;
    int i = 0;
    t.lexema[0] = '\0';
    int j = 0;

    while((c = fgetc(stdin)) != EOF){
        int col = obtener_columna(c);

        // Verificar si la columna es válida
        if (col == 99) {
            t.lexema[i++] = c;
            t.lexema[i] = '\0';
            t.token = ERROR_GENERAL;
            return t;
        }

        int nuevo_estado = tabla_transicion[estado][col];

        if (nuevo_estado == 99) {
            ungetc(c, stdin);
            t.lexema[i] = '\0'; 
            t.token = ERROR_GENERAL;
            return t;
        }

        t.lexema[i++] = c;
        estado = nuevo_estado;

        switch (estado) {
            case 2: // Identificador
                ungetc(c, stdin);
                t.lexema[--i] = '\0';
                t.token = IDENTIFICADOR;
                return t;

            case 4: // Constante
                ungetc(c, stdin);
                t.lexema[--i] = '\0';
                t.token = CONSTANTE;
                return t;

            case 5: // Más
                t.token = MAS;
                t.lexema[i] = '\0';
                return t;

            case 6: // Menos
                t.token = MENOS;
                t.lexema[i] = '\0';
                return t;

            case 7: // Paréntesis abre
                t.token = PARENTESIS_ABRE;
                t.lexema[i] = '\0';
                return t;

            case 8: // Paréntesis cierra
                t.token = PARENTESIS_CIERRA;
                t.lexema[i] = '\0';
                return t;

            case 9: // Coma
                t.token = COMA;
                t.lexema[i] = '\0';
                return t;

            case 10: // Punto y coma
                t.token = PUNTO_Y_COMA;
                t.lexema[i] = '\0';
                return t;

            case 12: // Asignación
                t.token = ASIGNACION;
                t.lexema[i] = '\0';
                return t;

            case 14: // Error falta '='
                t.token = ERROR_FALTA_IGUAL;
                t.lexema[i] = '\0';
                return t;

            case 15: // Multiplicación
                t.token = MULTIPLICACION;
                t.lexema[i] = '\0';
                return t;

            case 16: // División
                t.token = DIVISION;
                t.lexema[i] = '\0';
                return t;

            case 17: // Porcentaje
                t.token = PORCENTAJE;
                t.lexema[i] = '\0';
                return t;

            case 13: // Fin de archivo
                t.token = FDT;
                t.lexema[i] = '\0';
                return t;

            default:
                break;
        }

    }

    // Si se alcanza EOF fuera del bucle
    if (c == EOF) {
        t.token = FDT;
        t.lexema[i] = '\0';
        return t;
    }

    // Manejo adicional si es necesario
    t.token = ERROR_GENERAL;
    t.lexema[i] = '\0';
    return t;
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
            snprintf(buffer, sizeof(buffer), "Parentesis que abre '%s'", t.lexema);
            break;
        case COMA:
            snprintf(buffer, sizeof(buffer), "Coma '%s'", t.lexema);
            break;
        case PUNTO_Y_COMA:
            snprintf(buffer, sizeof(buffer), "Punto y Coma '%s'",t.lexema);
            break;
        case ASIGNACION:
            snprintf(buffer, sizeof(buffer), "Asignacion '%s'", t.lexema);
            break;
        case MULTIPLICACION:
            snprintf(buffer,sizeof(buffer), "Multiplicacion '%s'",t.lexema);
            break;
        case DIVISION:
            snprintf(buffer,sizeof(buffer),"Division '%s'",t.lexema);
            break;
        case PORCENTAJE:
            snprintf(buffer,sizeof(buffer),"Porcentaje '%s'",t.lexema);
            break;
        case FDT:
            snprintf(buffer,sizeof(buffer),"Fin de archivo '%s'",t.lexema);
            break;
        case ERROR_GENERAL:
            snprintf(buffer, sizeof(buffer), "Error general '%s'", t.lexema);
            break;
        case ERROR_FALTA_IGUAL:
            snprintf(buffer, sizeof(buffer), "Error: falta '=' '%s'", t.lexema);
            break;
        case ERROR_FALTA_DOS_PUNTOS:
            snprintf(buffer, sizeof(buffer), "Error: falta ':' '%s'", t.lexema);
            break;   
        default:
            snprintf(buffer, sizeof(buffer), "Token desconocido '%s'", t.lexema);
            break;
    }

    return buffer;
}