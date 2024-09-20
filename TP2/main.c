#include <stdio.h>
#include "scanner.h"

int main() {
    Token t;

    do {
        t = obtener_token();
        printf("%s\n", token_a_string(t));
    } while (t.token != FDT);

    return 0;   
}
