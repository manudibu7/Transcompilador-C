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


int obtener_columna(char c) {
    if (isalpha(c)) return 0;  
    if (isdigit(c)) return 1;  
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
    return 15;  
}


// Función que convierte un token a su representación en string
const char* token_a_string(Token token) {
    switch (token.token) {
        case IDENTIFICADOR: return "Identificador";
        case CONSTANTE: return "Constante";
        case MAS: return "Más";
        case MENOS: return "Menos";
        case PARENTESIS_ABRE: return "Paréntesis que abre";
        case PARENTESIS_CIERRA: return "Paréntesis que cierra";
        case COMA: return "Coma";
        case PUNTO_Y_COMA: return "Punto y coma";
        case ASIGNACION: return "Asignación";
        case MULTIPLICACION: return "Multiplicación";
        case DIVISION: return "División";
        case PORCENTAJE: return "Porcentaje";
        case FDT: return "FDT (EOF)";
        case ERROR_GENERAL: return "Error general";
        case ERROR_FALTA_IGUAL: return "Error en asignación por : solo ':'";
        case ERROR_FALTA_DOS_PUNTOS: return "Error falta dos puntos";
        case ERROR_IDENTIFICADOR: return "Error de identificador (caracteres no válidos)";
        case ERROR_CONSTANTE: return "Error en constante (números seguidos de letras)";
        default: return "Desconocido";
    }
}

Token obtener_token() {
    Token t;
    int estado = 0;
    char c;
    int i = 0;
    int linea = 1, columna = 1;
    t.lexema[0] = '\0';

    // Leer y descartar espacios en blanco
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
            columna = 1;
        } else {
            columna++;
        }
    } while (isspace(c));

    // Comentarios: ignorar todo hasta el final de la línea
    if (c == '/' && (c = fgetc(stdin)) == '/') {
        while (c != '\n' && c != EOF) {
            c = fgetc(stdin);
        }
        return obtener_token(); // Volver a llamar para obtener el siguiente token
    }

    // Identificar paréntesis, coma y otros símbolos
    if (c == '(') {
        t.token = PARENTESIS_ABRE;
        t.lexema[i++] = c;
        t.lexema[i] = '\0';
        t.linea = linea;
        t.columna = columna;
        return t;
    }
    if (c == ')') {
        t.token = PARENTESIS_CIERRA;
        t.lexema[i++] = c;
        t.lexema[i] = '\0';
        t.linea = linea;
        t.columna = columna;
        return t;
    }
    if (c == ';') {
        t.token = PUNTO_Y_COMA;
        t.lexema[i++] = c;
        t.lexema[i] = '\0';
        t.linea = linea;
        t.columna = columna;
        return t;
    }
    if (c == ',') {
        t.token = COMA;  // Agregar coma como token
        t.lexema[i++] = c;
        t.lexema[i] = '\0';
        t.linea = linea;
        t.columna = columna;
        return t;
    }
    if (c == '+') {
        t.token = MAS;
        t.lexema[i++] = c;
        t.lexema[i] = '\0';
        t.linea = linea;
        t.columna = columna;
        return t;
    }
    if (c == '-') {
        t.token = MENOS;
        t.lexema[i++] = c;
        t.lexema[i] = '\0';
        t.linea = linea;
        t.columna = columna;
        return t;
    }
    if (c == '*') {
        t.token = MULTIPLICACION;
        t.lexema[i++] = c;
        t.lexema[i] = '\0';
        t.linea = linea;
        t.columna = columna;
        return t;
    }
    if (c == '/') {
        t.token = DIVISION;
        t.lexema[i++] = c;
        t.lexema[i] = '\0';
        t.linea = linea;
        t.columna = columna;
        return t;
    }
    if (c == '%') {
        t.token = MENOS;
        t.lexema[i++] = c;
        t.lexema[i] = '\0';
        t.linea = linea;
        t.columna = columna;
        return t;
    }
    if (c == '=' || c == ':') {
        char siguiente = fgetc(stdin);
        if (c == ':' && siguiente == '=') {
            t.token = ASIGNACION;
            t.lexema[i++] = ':';
            t.lexema[i++] = '=';
            t.lexema[i] = '\0';
            t.linea = linea;
            t.columna = columna;
            return t;
        } else if (c == '=') {
            t.token = ASIGNACION;
            t.lexema[i++] = c;
            t.lexema[i] = '\0';
            t.linea = linea;
            t.columna = columna;
            return t;
        } else {
            ungetc(siguiente, stdin);  // Deshacer el paso de lectura si no era ':='
        }
    }

    // Detectar identificadores y palabras reservadas
    if (isalpha(c)) {
        t.token = IDENTIFICADOR;
        t.lexema[i++] = c;
        while (isalnum(c = fgetc(stdin))) {
            t.lexema[i++] = c;
        }
        ungetc(c, stdin);  // Deshacer la lectura del último caracter no válido
        t.lexema[i] = '\0';

        // Verificar si es una palabra reservada
        if (strcmp(t.lexema, "entero") == 0 || strcmp(t.lexema, "leer") == 0 || strcmp(t.lexema, "escribir") == 0) {
            // Es palabra reservada, pero sigue siendo identificador
            t.token = IDENTIFICADOR;
        }
        t.linea = linea;
        t.columna = columna;
        return t;
    }

    // Detectar constantes
    if (isdigit(c)) {
        t.token = CONSTANTE;
        t.lexema[i++] = c;
        while (isdigit(c = fgetc(stdin))) {
            t.lexema[i++] = c;
        }
        ungetc(c, stdin);  // Deshacer la lectura del último caracter no válido
        t.lexema[i] = '\0';
        t.linea = linea;
        t.columna = columna;
        return t;
    }

    // Manejo de errores: Común, identificador o constante
    if (isalpha(c)) {
        t.token = ERROR_IDENTIFICADOR;
    } else if (isdigit(c)) {
        t.token = ERROR_CONSTANTE;
    } else {
        // Acumular caracteres inválidos hasta encontrar un espacio o un separador
        t.token = ERROR_GENERAL;
        t.lexema[i++] = c;
        while (isalnum(c = fgetc(stdin)) || c == '@' || c == '#' || c == '!') {
            t.lexema[i++] = c;
        }
        ungetc(c, stdin);  // Deshacer la lectura del último caracter no válido
        t.lexema[i] = '\0';
        t.linea = linea;
        t.columna = columna;
    }
    return t;
}


