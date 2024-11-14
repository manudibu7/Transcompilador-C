%{
#include <stdio.h>
#include "tokens.h"
%}

%%

"programa" { return PROGRAMA;}
"entero" { return ENTERO;}
"leer" { return LEER;}
"escribir" { return ESCRIBIR;}
"fin" { return FIN;}
":=" { return ASIGNACION;}
"+" { return MAS;}
"-" { return MENOS;}
"(" { return PARENTESIS_ABRE;}
")" { return PARENTESIS_CIERRA;}
"," { return COMA;}
";" { return PUNTO_Y_COMA;}
"*" { return MULTIPLICACION;}
"/" { return DIVISION;}
"%" { return PORCENTAJE;}

[a-zA-Z][a-zA-Z0-9]* {return IDENTIFICADOR;}

[0-9]+ {return CONSTANTE;}

"//".* {}
[ ] {}
[\t\n ]+ {}

[@!:#=$]+ {printf("Error lexico: cadena desconocida %s\n", yytext); return ERROR;} //revisar caracteres invalidos
[a-zA-Z][a-zA-Z0-9]*[@!:#=$]+[a-zA-Z0-9@!:#=$]* {printf("Error lexico: identificador invalido %s\n", yytext); return ERROR;}
[0-9]+[a-zA-Z][a-zA-Z0-9]* {printf("Error lexico: constante invalida %s\n", yytext); return ERROR;}

<<EOF>> {return FDT;}

%%

int yywrap(void){
    return 1;
}
