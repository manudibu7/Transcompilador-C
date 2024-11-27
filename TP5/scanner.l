%top{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"
int errlex;
char buffer[200];
extern int yylineno;
}


%option yylineno
%%

\n              { yylineno++; }
"programa"      return PROGRAMA;
"entero"        return ENTERO;
"leer"          return LEER;
"escribir"      return ESCRIBIR;
"fin"           return FIN;
":="            return ASIGNACION;
"+"             return '+';
"-"             return '-';
"*"             return '*';
"/"             return '/';
"%"             return '%';
"("             return PARENTESIS_ABRE;
")"             return PARENTESIS_CIERRA;
","             return ',';
";"             return ';';

[a-zA-Z][a-zA-Z0-9]* { yylval = strdup(yytext); return IDENTIFICADOR; }
[0-9]+ { yylval = strdup(yytext); return CONSTANTE; }

"//".* {} 
[ \t\n]+ {}

[!@#$^&?`~=:'"><.'|]+ {
    fprintf(stderr, "línea #%d: Error léxico: cadena desconocida: %s\n", yylineno, yytext);
    errlex++;
}

%%

int yywrap(void) {
                return 1;
}
