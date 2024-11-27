#include <stdio.h>

int yyparse();

int main(){
    if(yyparse() == 0){
    }else{
        printf("error en el Analisis Sintactico\n");
    }
    return 0;
}