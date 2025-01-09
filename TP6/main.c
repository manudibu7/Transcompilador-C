
#include <stdio.h>
#include "parser.h"
#include "scanner.h"
#include "semantic.h"
#include "symbol.h"

int yynerrs = 0;
int semerrs = 0;

int main(){
	switch (yyparse()){
    case 0:
        puts("Compilación exitosa");
        printf("Errores sintácticos: %d, Errores léxicos %d y Errores semánticos: %d\n",yynerrs,errlex,semerrs);
        return 0;

    case 1:
        puts("Error de compilación");
        printf("Errores sintácticos: %d, Errores léxicos %d y Errores semánticos: %d\n",yynerrs,errlex,semerrs);
        return 1;

    case 2:
        puts("Memoria insuficiente\n");
        return 2;
    }
    return 0;
}