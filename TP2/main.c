#include <stdio.h>
#include "scanner.h"

int main() {
    Token token;
    while (token != FDT){
        token = scanner();
        print_token(token);  
    }
    return 0;
}