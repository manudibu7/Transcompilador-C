#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "semantic.h"

extern simbolo_t *tabla_de_simbolos;

static int cont_temp = 1;

static char *nuevo_temporal(void) {
    char buffer[64];
    sprintf(buffer, "_Temp%d", cont_temp++);
    char *temp = strdup(buffer);
    // Imprime la declaración de la variable temporal.
    printf("    int %s;\n", temp);
    return temp;
}

void inicializar(char *nom_programa) {
    // Reinicializa la tabla de símbolos.
    tabla_de_simbolos = NULL;
    
    // Imprime la cabecera del programa.
    printf("#include <stdio.h>\n\n");
    printf("int main(void) {\n");
    
    // Se podría utilizar 'nom_programa' para algún tratamiento especial.
    free(nom_programa);
}

void finalizar(void) {
    borrar_simbolos(&tabla_de_simbolos);
    printf("    return 0;\n");
    printf("}\n");
}

int declarar(char *identificador) {
    if (contiene_simbolo(tabla_de_simbolos, identificador) != 0) {
        simbolo_t *simbolo = nuevo_simbolo(identificador);
        agregar_simbolo(&tabla_de_simbolos, simbolo);
        printf("    int %s;\n", identificador);
        return 0;
    }
    yysemerrs++;
    fprintf(stderr, "Error semantico: identificador %s ya declarado\n", identificador);
    return -1;
}

int declarado(char *identificador) {
    if (contiene_simbolo(tabla_de_simbolos, identificador) == 0)
        return 1;
    yysemerrs++;
    fprintf(stderr, "Error semantico: identificador %s NO declarado\n", identificador);
    return -1;
}

void asignar(char *id, char *expr) {
    if (contiene_simbolo(tabla_de_simbolos, id) == 0) {
        printf("    %s = %s;\n", id, expr);
    } else {
        yysemerrs++;
        fprintf(stderr, "Error semantico: identificador %s NO declarado\n", id);
    }
    free(id);
    free(expr);
}

void leer(char *id) {
    if (contiene_simbolo(tabla_de_simbolos, id) == 0) {
        printf("    scanf(\"%%d\", &%s);\n", id);
    } else {
        yysemerrs++;
        fprintf(stderr, "Error semantico: identificador %s NO declarado\n", id);
    }
    free(id);
}

void escribir(char *expr) {
    printf("    printf(\"%%d\\n\", %s);\n", expr);
    free(expr);
}

char *operar(char *opIzq, char op, char *opDer) {
    char *temp = nuevo_temporal();
    printf("    %s = %s %c %s;\n", temp, opIzq, op, opDer);
    free(opIzq);
    free(opDer);
    return temp;
}

char *negar(char *expr) {
    char *temp = nuevo_temporal();
    printf("    %s = -%s;\n", temp, expr);
    free(expr);
    return temp;
}
