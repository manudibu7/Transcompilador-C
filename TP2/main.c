#include <stdio.h>
#include "scanner.h"
#include <stdio.h>
#include "scanner.h"

int main() {
    Token t;
    while ((t = obtener_token()).token != FDT) {
        if (t.token == ERROR_GENERAL) {
            printf("Error general '%s'\n", t.lexema);
        } else if (t.token == ERROR_IDENTIFICADOR) {
            printf("Error en identificador '%s'\n", t.lexema);
        } else if (t.token == ERROR_CONSTANTE) {
            printf("Error en constante '%s'\n", t.lexema);
        } else {
            printf("%s '%s'\n", token_a_string(t), t.lexema);
        }
    }
    return 0;
}

