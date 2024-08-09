#include <stdio.h>
#include <stdlib.h>
#include "tabla.h"

int main(int argc, char *argv[]){

    if(argc < 3){
        printf("Uso %s <inicio> <fin> [incremento]\n", argv[0]);
        return 1;
    }

    float inicio = atof(argv[1]);
    float fin = atof(argv[2]);
    float incremento =  1.0;
    //(argc > 3) ? atof(argv[3]) :

      if (argc >= 4) {
        incremento = atof(argv[3]);
    }

    estructuraTabla(inicio, fin, incremento);


    return 0;
}


/*
|--resultados.?? // Archivo con los resultados
|-- main.c // Inicio del programa
|-- makefile // Recetas para construir el ejecutable
|-- conversion.c // Definiciones para convertir
|-- conversion.h // Declaraciones para convertir
|-- conversion.i // Preprocesado de conversion.c
|-- tabla.c // Definiciones para armar la tabla
|-- tabla.h // Declaraciones para armar la tabla
*/