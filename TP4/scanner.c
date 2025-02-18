#include "scanner.h"
#include <stdio.h>
#include <ctype.h>
#include <string.h>


int tabla_transicion[19][16] = {
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


const char* token_a_string(Token token) {
    switch (token.token) {
        case PROGRAMA:        return "Programa";
        case FIN:             return "fin";
        case ENTERO:          return "entero";
        case LEER:            return "leer";
        case ESCRIBIR:        return "escribir";
        case IDENTIFICADOR:   return "Identificador";
        case CONSTANTE:       return "Constante";
        case MAS:             return "Más";
        case MENOS:           return "Menos";
        case PARENTESIS_ABRE: return "Paréntesis que abre";
        case PARENTESIS_CIERRA:return "Paréntesis que cierra";
        case COMA:            return "Coma";
        case PUNTO_Y_COMA:    return "Punto y coma";
        case ASIGNACION:      return "Asignación";
        case MULTIPLICACION:  return "Multiplicación";
        case DIVISION:        return "División";
        case PORCENTAJE:      return "Porcentaje";
        case FDT:             return "FDT (EOF)";
        case ERROR_GENERAL:   return "Error general";
        case ERROR_FALTA_IGUAL:    return "Error en asignación por : solo ':'";
        case ERROR_FALTA_DOS_PUNTOS: return "Error en asignación por = solo '='";
        case ERROR_IDENTIFICADOR:  return "Error de identificador (caracteres no válidos)";
        case ERROR_CONSTANTE:      return "Error en constante (números seguidos de letras)";
        default: return "Desconocido";
    }
}


Token obtener_token() {
    Token t;
    char c;
    int i = 0;
   
    static int linea = 1, columna = 0;
    t.lexema[0] = '\0';

    
    do {
        c = fgetc(stdin);
        if (c == EOF) {
            t.token = FDT;
            t.lexema[0] = '\0';
            t.linea = linea;
            t.columna = columna;
            return t;
        }
        if (c == '\n') {
            linea++;
            columna = 0;
        } else {
            columna++;
        }
    } while (isspace(c));

    
    if (c == '/') {
        char next = fgetc(stdin);
        if (next == '/') {
            while (c != '\n' && c != EOF)
                c = fgetc(stdin);
            return obtener_token();
        } else {
            ungetc(next, stdin);
        }
    }

   
    if (c == '(') {
        t.token = PARENTESIS_ABRE;
        t.lexema[i++] = c;
        t.lexema[i] = '\0';
        t.linea = linea; t.columna = columna;
        return t;
    }
    if (c == ')') {
        t.token = PARENTESIS_CIERRA;
        t.lexema[i++] = c;
        t.lexema[i] = '\0';
        t.linea = linea; t.columna = columna;
        return t;
    }
    if (c == ';') {
        t.token = PUNTO_Y_COMA;
        t.lexema[i++] = c;
        t.lexema[i] = '\0';
        t.linea = linea; t.columna = columna;
        return t;
    }
    if (c == ',') {
        t.token = COMA;
        t.lexema[i++] = c;
        t.lexema[i] = '\0';
        t.linea = linea; t.columna = columna;
        return t;
    }
    if (c == '+') {
        t.token = MAS;
        t.lexema[i++] = c;
        t.lexema[i] = '\0';
        t.linea = linea; t.columna = columna;
        return t;
    }
    if (c == '-') {
        t.token = MENOS;
        t.lexema[i++] = c;
        t.lexema[i] = '\0';
        t.linea = linea; t.columna = columna;
        return t;
    }
    if (c == '*') {
        t.token = MULTIPLICACION;
        t.lexema[i++] = c;
        t.lexema[i] = '\0';
        t.linea = linea; t.columna = columna;
        return t;
    }
    if (c == '/') {
        t.token = DIVISION;
        t.lexema[i++] = c;
        t.lexema[i] = '\0';
        t.linea = linea; t.columna = columna;
        return t;
    }
    if (c == '%') {
        t.token = PORCENTAJE;  
        t.lexema[i++] = c;
        t.lexema[i] = '\0';
        t.linea = linea; t.columna = columna;
        return t;
    }
   
    if (c == ':' || c == '=') {
        char siguiente = fgetc(stdin);
        if (c == ':' && siguiente == '=') {
            t.token = ASIGNACION;
            t.lexema[i++] = ':';
            t.lexema[i++] = '=';
            t.lexema[i] = '\0';
            t.linea = linea; t.columna = columna;
            return t;
        } else {
            ungetc(siguiente, stdin);
            if (c == ':')
                t.token = ERROR_FALTA_IGUAL;
            else  // c == '='
                t.token = ERROR_FALTA_DOS_PUNTOS;
            t.lexema[i++] = c;
            t.lexema[i] = '\0';
            t.linea = linea; t.columna = columna;
            return t;
        }
    }
   
    if (isalpha(c)) {
        t.lexema[i++] = c;
        while (isalnum(c = fgetc(stdin)))
            t.lexema[i++] = c;
        ungetc(c, stdin);
        t.lexema[i] = '\0';
        
        if (strcmp(t.lexema, "programa") == 0)
            t.token = PROGRAMA;
        else if (strcmp(t.lexema, "entero") == 0)
            t.token = ENTERO;
        else if (strcmp(t.lexema, "leer") == 0)
            t.token = LEER;
        else if (strcmp(t.lexema, "escribir") == 0)
            t.token = ESCRIBIR;
        else if (strcmp(t.lexema, "fin") == 0)
            t.token = FIN;
        else
            t.token = IDENTIFICADOR;
        t.linea = linea; t.columna = columna;
        return t;
    }
    
    if (isdigit(c)) {
        t.lexema[i++] = c;
        while (isdigit(c = fgetc(stdin)))
            t.lexema[i++] = c;
        ungetc(c, stdin);
        t.lexema[i] = '\0';
        t.token = CONSTANTE;
        t.linea = linea; t.columna = columna;
        return t;
    }

    t.token = ERROR_GENERAL;
    t.lexema[i++] = c;
    while ((c = fgetc(stdin)) != EOF &&
           !isspace(c) && c!='(' && c!=')' && c!=';' && c!=',' &&
           c!='+' && c!='-' && c!='*' && c!='/' && c!='%' &&
           c!=':' && c!='=') {
        t.lexema[i++] = c;
    }
    if (c != EOF)
        ungetc(c, stdin);
    t.lexema[i] = '\0';
    t.linea = linea; t.columna = columna;
    return t;
}

