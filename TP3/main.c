#include <stdio.h>
#include "tokens.h"

extern int yylex();
extern char* yytext;

void token_a_string(t_token token) {

    switch (token) {
        case PROGRAMA:
            printf("Token: Programa\n");
            break;
        case IDENTIFICADOR:
            printf("Token: Identificador  lexema: %s\n",yytext);
            break;
        case CONSTANTE:
            printf("Token: Constante   lexema: %s\n", yytext);
            break;
        case FIN:
            printf("Token: Fin\n");
            break;
        case ENTERO:
            printf("Token: Entero\n");
            break;
        case LEER:
            printf("Token: Leer\n");
            break;
        case ESCRIBIR:
            printf("Token: Escribir\n");
            break;
        case ERROR:
            break;
        case ASIGNACION:
            printf("Token: Asignacion\n");
            break;
        case MAS:
            printf("Token: '+'\n");
            break;
        case MENOS:
            printf("Token: '-'\n");
            break;
        case PARENTESIS_ABRE:
            printf("Token: '('\n");
            break;
        case PARENTESIS_CIERRA:
            printf("Token: ')'\n");
            break;
        case COMA:
            printf("Token: ','\n");
            break;
        case PUNTO_Y_COMA:
            printf("Token: ';'\n");
            break;
        case MULTIPLICACION:
            printf("Token: '*'\n");
            break;
        case DIVISION:
            printf("Token: '/'\n");
            break;
        case PORCENTAJE:
            printf("Token: '%%'\n");
            break;
        default:
            printf("TOKEN DESCONOCIDO\n");
            break;
    }
}

int main(){
    t_token token;
    while((token = yylex()) != FDT){
        token_a_string(token);
    }
    printf("Token: Fin de Archivo");
    return 0;
}