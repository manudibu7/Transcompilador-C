%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"

int erroresLexicos = 0;  // Contador de errores léxicos
char buffer[200];
extern int yylineno;  // Línea actual para mensajes de error
%}

%option yylineno

%%

"programa"      { return PROGRAMA; }
"entero"        { return ENTERO; }
"leer"          { return LEER; }
"escribir"      { return ESCRIBIR; }
"fin"           { return FIN; }
":="            { return ASIGNACION; }
"+"             { return '+'; }
"-"             { return '-'; }
"*"             { return '*'; }
"/"             { return '/'; }
"%"             { return '%'; }
"("             { return PARENTESIS_ABRE; }
")"             { return PARENTESIS_CIERRA; }
","             { return ','; }
";"             { return ';'; }

[a-zA-Z][a-zA-Z0-9]*  { yylval = strdup(yytext); return IDENTIFICADOR; }
[0-9]+               { yylval = strdup(yytext); return CONSTANTE; }

"//".*              { /* Ignorar comentarios */ }
[ \t\n]+            { /* Ignorar espacios y saltos de línea */ }

. {
    fprintf(stderr, "Línea #%d: Error léxico: cadena desconocida: %s\n", yylineno, yytext);
    erroresLexicos++;
}

%%

int yywrap(void) {
    return 1;
}