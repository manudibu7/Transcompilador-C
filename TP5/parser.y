%code top{
    #include <stdio.h>
    #include "scanner.h"
}

%code provides{
    void yyerror(const char *);
    extern int yylexerrs;
}

%defines "parser.h"
%output "parser.c"

%define api.value.type {char *}
%define parse.error verbose

%token IDENTIFICADOR CONSTANTE PROGRAMA ENTERO LEER ESCRIBIR FIN_PROGRAMA ASIGNACION

%start programa

%left '+' '-'
%left '*' '/' '%'

%precedence NEG   

%%

programa
    : PROGRAMA IDENTIFICADOR { printf("programa %s\n", $IDENTIFICADOR); } logica FIN_PROGRAMA { if (yynerrs || yylexerrs) YYABORT; else YYACCEPT; }
    ;

logica
    : sentencia
    | logica sentencia
    ;

sentencia
    : identificador ASIGNACION expresion ';' { printf("Sentencia asignacion: %s\n", yylval); free(yylval); }
    | ENTERO IDENTIFICADOR ';' { printf("Sentencia declaracion: %s\n", yylval); free(yylval); }
    | LEER '(' lista-de-identificadores ')' ';' { printf("Sentencia leer\n"); }
    | ESCRIBIR '(' lista-de-expresiones ')' ';' { printf("Sentencia escribir\n"); }
    | error ';'
    ;

lista-de-identificadores
    : identificador
    | lista-de-identificadores ',' IDENTIFICADOR
    ;

lista-de-expresiones
    : expresion
    | lista-de-expresiones ',' expresion
    ;

expresion
    : identificador
    | CONSTANTE
    | '(' expresion ')' { printf("abre parentesis\n"); printf("cierra parentesis\n"); }
    | '-' expresion %prec NEG { printf("negacion\n"); }
    | expresion '*' expresion { printf("multiplicacion\n"); }
    | expresion '/' expresion { printf("division\n"); }
    | expresion '%' expresion { printf("modulo\n"); }
    | expresion '+' expresion { printf("suma\n"); }
    | expresion '-' expresion { printf("resta\n"); }
    ;

identificador
    : IDENTIFICADOR
    ;

%%

/* Informa la ocurrencia de un error. */
void yyerror(const char *s){
	printf("linea #%d: %s\n", yylineno, s);
	return;
}