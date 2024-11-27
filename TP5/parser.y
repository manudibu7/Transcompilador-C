%code top{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    int errlex = 0;
    int errsin = 0;
    extern int yylineno;
}

%code provides {
    void yyerror(const char *s);
    int yylex();
    extern int errlex;
    extern int errsin;
    extern int yylineno;
}

%defines "parser.h"
%output "parser.c"
%define api.value.type {char*}
%define parse.error detailed

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
        printf("Programa: %s\n", $2);
    } listaSentencias FIN {
        if(errsin > 0 || errlex > 0){printf("Errores de compilacion\n");}
        else{printf("Compilación terminada con éxito\n");}
        printf("Errores sintacticos: %d - Errores lexicos: %d\n", errsin, errlex);
    }
;

listaSentencias:
    sentencia
    | listaSentencias sentencia
;

sentencia:
    ENTERO IDENTIFICADOR ';' {printf("Sentencia declaracion: %s\n", $2);}
    | IDENTIFICADOR ASIGNACION expresion ';' {printf("Sentencia asignacion\n");}
    | LEER PARENTESIS_ABRE listaIdentificadores PARENTESIS_CIERRA ';' {printf("Sentencia leer\n");}
    | ESCRIBIR PARENTESIS_ABRE listaExpresiones PARENTESIS_CIERRA ';' {printf("Sentencia escribir\n");}
    | error ';'
;

listaIdentificadores:
    IDENTIFICADOR
    | listaIdentificadores ',' IDENTIFICADOR
;

listaExpresiones:
    expresion
    | listaExpresiones ',' expresion
;

expresion:
    termino
    | expresion '+' termino {printf("operacion de suma\n");}
    | expresion '-' termino {printf("operacion de resta\n");}
;

termino:
    primaria
    | termino '*' primaria {printf("operacion de multiplicacion\n");}
    | termino '/' primaria {printf("operacion de division\n");}
    | termino '%' primaria {printf("operacion de modulo\n");}
;

primaria:
    IDENTIFICADOR
    | CONSTANTE
    | PARENTESIS_ABRE {printf("parentesis abre\n");}
        expresion 
        PARENTESIS_CIERRA {printf("parentesis cierra\n");}
    | '-' primaria %prec UMINUS {printf("operacion de inversion\n");}
;

%%

void yyerror(const char *s) {
    printf("línea #%d: %s\n", yylineno, s);
    errsin++;
}