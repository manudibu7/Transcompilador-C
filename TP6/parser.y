%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symbol.h"
#include "semantic.h"

// varialbes para el conteo de errores
int erroresLexicos = 0;
int erroresSintacticos = 0;
int erroresSemanticos = 0;

// linea actual para los mensajes de error
extern int yylineno;
%}

%code provides {
    void yyerror(const char *mensaje);
    int yylex();
    extern int erroresLexicos;
    extern int erroresSintacticos;
    extern int erroresSemanticos;
    extern int yylineno;
}

%start programa

%token PROGRAMA ENTERO LEER ESCRIBIR FIN
%token ASIGNACION '+' '-' '*' '/' '%'
%token IDENTIFICADOR CONSTANTE
%token PARENTESIS_ABRE PARENTESIS_CIERRA ',' ';'

%right UMINUS
%left '+' '-'
%left '*' '/' '%'

%%

programa:
    PROGRAMA IDENTIFICADOR {
        printf("#include <stdio.h>\n");
        printf("int main() {\n");
        printf("// Programa: %s\n", $2);
    }
    listaSentencias FIN {
        printf("return 0;\n}\n");
        limpiarTabla();  // Limpiar la tabla de símbolos al final
    }
;

listaSentencias:
    sentencia
    | listaSentencias sentencia
;

sentencia:
    ENTERO IDENTIFICADOR ';' {
        if (declararVariable($2)) {
            erroresSemanticos++;
            YYERROR;
        }
    }
    | IDENTIFICADOR ASIGNACION expresion ';' {
        if (verificarVariableDeclarada($1)) {
            erroresSemanticos++;
            YYERROR;
        }
        generarAsignacion($1, $3);
    }
    | LEER PARENTESIS_ABRE listaIdentificadores PARENTESIS_CIERRA ';' {
        generarLectura($3);
    }
    | ESCRIBIR PARENTESIS_ABRE listaExpresiones PARENTESIS_CIERRA ';' {
        generarEscritura($3);
    }
    | error ';' {
        printf("// Error sintáctico en la línea %d\n", yylineno);
        erroresSintacticos++;
        YYERROR;
    }
;

listaIdentificadores:
    IDENTIFICADOR {
        if (verificarVariableDeclarada($1)) {
            erroresSemanticos++;
            YYERROR;
        }
        $$ = $1;
    }
    | listaIdentificadores ',' IDENTIFICADOR {
        if (verificarVariableDeclarada($3)) {
            erroresSemanticos++;
            YYERROR;
        }
        $$ = $3;
    }
;

listaExpresiones:
    expresion {
        $$ = $1;
    }
    | listaExpresiones ',' expresion {
        $$ = generarOperacionInfija($1, ",", $3);
    }
;

expresion:
    termino {
        $$ = $1;
    }
    | expresion '+' termino {
        $$ = generarOperacionInfija($1, "+", $3);
    }
    | expresion '-' termino {
        $$ = generarOperacionInfija($1, "-", $3);
    }
;

termino:
    primaria {
        $$ = $1;
    }
    | termino '*' primaria {
        $$ = generarOperacionInfija($1, "*", $3);
    }
    | termino '/' primaria {
        $$ = generarOperacionInfija($1, "/", $3);
    }
    | termino '%' primaria {
        $$ = generarOperacionInfija($1, "%", $3);
    }
;

primaria:
    IDENTIFICADOR {
        if (verificarVariableDeclarada($1)) {
            erroresSemanticos++;
            YYERROR;
        }
        $$ = $1;
    }
    | CONSTANTE {
        $$ = $1;
    }
    | PARENTESIS_ABRE expresion PARENTESIS_CIERRA {
        $$ = $2;
    }
    | '-' primaria %prec UMINUS {
        $$ = generarOperacionInfija("0", "-", $2);
    }
;

%%

void yyerror(const char *mensaje) {
    printf("// Error en la línea %d: %s\n", yylineno, mensaje);
    erroresSintacticos++;
}
