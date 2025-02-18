#include <stdio.h>
#include <stdlib.h>

#include "parser.h"
#include "scanner.h"

#define YYACCEPT 0
#define YYABORT 1
#define YYNOMEM 2

int yylexerrs = 0; //error lexico
int yysemerrs = 0; //erorr semantico

extern int yynerrs; //error sintactico

int main(void)
{
    unsigned int exit_code = 0;

    switch (yyparse())
    {
    case YYACCEPT:
        printf("Compilacion terminada con exito\n");
        exit_code = YYACCEPT;
        break;
    case YYABORT:
        printf("Errores de compilacion\n");
        exit_code = YYABORT;
        break;
    case YYNOMEM:
        printf("Memoria insuficiente\n");
        exit_code = YYNOMEM;
        break;
    }

    printf("Errores sintacticos: %d - Errores lexicos: %d - Errores semanticos: %d\n", yynerrs, yylexerrs, yysemerrs);

    return exit_code;
}