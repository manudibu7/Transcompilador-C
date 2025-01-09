
#include <stdio.h>
#include "parser.h"
#include "scanner.h"
#include <stdio.h>
#include <stdlib.h>



int yyparse();

extern int erroresLexicos;
extern int erroresSintacticos;
extern int erroresSemanticos;

int main() {
    // Llamamos al parser
    if (yyparse() == 0) {
    } else {
        printf("Errores encontrados:\n");
        if (erroresLexicos > 0) printf(" - Léxicos: %d\n", erroresLexicos);
        if (erroresSintacticos > 0) printf(" - Sintácticos: %d\n", erroresSintacticos);
        if (erroresSemanticos > 0) printf(" - Semánticos: %d\n", erroresSemanticos);
    }

    return 0;
}