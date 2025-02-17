#include <stdio.h>
#include <stdlib.h>

#include "parser.h"

#define YYACCEPT 0
#define YYABORT 1
#define YYNOMEM 2

int yylexerrs = 0;
extern int yynerrs;

int main(void)
{
    switch( yyparse() )
    {
        case YYACCEPT:
            printf("Compilacion terminada con exito\n");
            break;
        case YYABORT:
            printf("Errores de compilacion\n");
            break;
        case YYNOMEM:
            printf("Memoria insuficiente\n");
            break;
    }

    printf("Errores sintacticos: %d - Errores lexicos: %d\n", yynerrs, yylexerrs);

    return 0;
}