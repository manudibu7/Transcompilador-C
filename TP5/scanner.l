%{

#include <stdio.h>
#include "parser.h"

#define ERROR_LEXICO(mensaje) yylexerrs++; char buffer[128]; sprintf(buffer, "Error léxico: %s: %s", mensaje, yytext ); yyerror(buffer);

%}

%option outfile="scanner.c"
%option header-file="scanner.h"

%option noyywrap
%option nounput
%option noinput
%option yylineno

espacio_en_blanco [[:space:]]
comentario \/\/[^\n]*
caracter_invalido [~`!@#$^&\[}[\]'"?\\>]

letra [[:alpha:]]
digito [[:digit:]]

operador_primario [+-]
operador_secundario [*/%]

identificador {letra}({letra}|{digito})*
constante {digito}+
palabra_reservada programa|entero|leer|escribir|fin-programa
asignacion :=

%%

"programa" { return PROGRAMA; }

"entero" { return ENTERO; }

"leer" { return LEER; }

"escribir" { return ESCRIBIR; }

"fin" { return FIN_PROGRAMA; }

{espacio_en_blanco}+ {} /* ignorar nuevas lineas, tabuladores y espacios */

{comentario} {} /* ignorar comentarios */

{caracter_invalido}+ { ERROR_LEXICO("cadena inválida"); }

{asignacion} { return ASIGNACION; }

{identificador} { yylval = strdup(yytext); return IDENTIFICADOR; }

{constante} { yylval = strdup(yytext); return CONSTANTE; }

{constante}({caracter_invalido}|{letra})({caracter_invalido}|{letra}|{digito})* { ERROR_LEXICO("constante inválida"); }

{identificador}{caracter_invalido}({caracter_invalido}|{letra}|{digito})*  { ERROR_LEXICO("identificador inválido"); }

"+" { return '+'; }

"-" { return '-'; }

"*" { return '*'; }

"/" { return '/'; }

"%" { return '%'; }

"(" { return '('; }

")" { return ')'; }

"," { return ','; }

";" { return ';'; }

. { ERROR_LEXICO("caracter desconocido"); }

%%
