#include "parser.h"
#include <stdio.h>

bool noHuboError = true;
Token tokenActual;
t_token token;

void obtenerProximoToken() {
    tokenActual = obtener_token();
}

void mostrarFin() {
    printf("%s\n", token_a_string(tokenActual));
}

void errorSintactico(){
    noHuboError = false;
    token = tokenActual.token;
    if(token == ERROR_FALTA_DOS_PUNTOS || token == ERROR_FALTA_IGUAL)
        printf("%s\n", token_a_string(tokenActual));
    else if(token == ERROR_GENERAL)
        printf("Error general '%s'\n", tokenActual.lexema);
    else
        printf("ERROR Sintáctico, no se esperaba el token %s\n", token_a_string(tokenActual));
}

void match(t_token esperado) {
    if(noHuboError) {
        if (tokenActual.token == esperado) {
            if (esperado != FIN) //asi finaliza solo 
                obtenerProximoToken();
        } else {
            noHuboError = false;
            errorSintactico();
            if (esperado != FIN)
                obtenerProximoToken();
        }
    }
}

void parser() {
    obtenerProximoToken();
    printf("Programa: ");
    match(PROGRAMA);

    if (tokenActual.token == IDENTIFICADOR)
        printf("%s\n", tokenActual.lexema);
    else
        printf("%s\n", tokenActual.lexema);
    match(IDENTIFICADOR);
    listaSentencias();
    match(FIN);
}

void listaSentencias() {
    while (tokenActual.token != FIN && tokenActual.token != FDT)
        sentencia();
    mostrarFin();
}

void sentencia() {
    noHuboError = true;
    if (tokenActual.token == ENTERO) {
        match(ENTERO);
        match(IDENTIFICADOR);
        match(PUNTO_Y_COMA);
        if(noHuboError)
            printf("Sentencia declaración\n");
        noHuboError = true;
    }
    else if (tokenActual.token == IDENTIFICADOR) {
        match(IDENTIFICADOR);
        
        if (tokenActual.token == ASIGNACION || tokenActual.token == ERROR_FALTA_IGUAL || tokenActual.token == ERROR_FALTA_DOS_PUNTOS)
            match(tokenActual.token);
        else {
            errorSintactico();
            obtenerProximoToken();
            return;
        }
        expresion();
        match(PUNTO_Y_COMA);
        if(noHuboError)
            printf("Sentencia asignación\n");
        noHuboError = true;
    }
    else if (tokenActual.token == LEER) {
        match(LEER);
        match(PARENTESIS_ABRE);
        listaIdentificadores();
        match(PARENTESIS_CIERRA);
        match(PUNTO_Y_COMA);
        if(noHuboError)
            printf("Sentencia leer\n");
        noHuboError = true;
    }
    else if (tokenActual.token == ESCRIBIR) {
        match(ESCRIBIR);
        match(PARENTESIS_ABRE);
        listaExpresiones();
        match(PARENTESIS_CIERRA);
        match(PUNTO_Y_COMA);
        if(noHuboError)
            printf("Sentencia escribir\n");
        noHuboError = true;
    }
    else {
        errorSintactico();
        obtenerProximoToken();
    }
}

void listaIdentificadores() {
    match(IDENTIFICADOR);
    while (tokenActual.token == COMA) {
        match(COMA);
        match(IDENTIFICADOR);
    }
}

void listaExpresiones() {
    expresion();
    while (tokenActual.token == COMA) {
        match(COMA);
        expresion();
    }
}

void expresion() {
    termino();
    while (tokenActual.token == MAS || tokenActual.token == MENOS) {
        obtenerProximoToken();
        termino();
    }
}

void termino() {
    primaria();
    while (tokenActual.token == MULTIPLICACION || tokenActual.token == DIVISION || tokenActual.token == PORCENTAJE) {
        obtenerProximoToken();
        primaria();
    }
}

void primaria() {
    if (tokenActual.token == IDENTIFICADOR)
        match(IDENTIFICADOR);
    else if (tokenActual.token == CONSTANTE)
        match(CONSTANTE);
    else if (tokenActual.token == PARENTESIS_ABRE) {
        match(PARENTESIS_ABRE);
        expresion();
        match(PARENTESIS_CIERRA);
    }
    else if (tokenActual.token == MENOS) {
        match(MENOS);
        primaria();
    }
    else {
        errorSintactico();
        obtenerProximoToken();
    }
}
