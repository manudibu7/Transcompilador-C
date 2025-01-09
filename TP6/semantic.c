#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "symbol.h"
#include "semantic.h"

int variablesTemporales = 0;

void declarar(char* identificador){
	printf("Reserve %s, 4\n",identificador);
}

char* nuevoTemporal(){
	char nuevoTemporal[10];
	variablesTemporales+=1;
	sprintf(nuevoTemporal, "Temp#%d", variablesTemporales);
	declarar(nuevoTemporal);
	return strdup(nuevoTemporal);
}


char* menosUnario(char* variable){
  	char* aux;
	aux = nuevoTemporal();
	printf("NEG %s, %s\n", variable, aux);
	return aux;
}


void asignar(char* expresion, char* identificador){
	printf("Store %s in %s \n", expresion, identificador);
}

void empezar(){
	printf("Load rtlib,\n");
}
void finalizar(){
	printf("Exit\n");
}

void leer(char* identificador){
	printf("Read %s, Integer\n", identificador);
}

void escribir(char* identificador){
	printf("Write %s, Integer\n", identificador);
}

char* sumar(char *identificador1, char *identificador2){
	char* salida;
	salida = nuevoTemporal();
	printf("ADD %s, %s, %s\n",identificador1,identificador2,salida);
	return salida;
}
char* restar(char *identificador1, char *identificador2){
	char* salida;
	salida = nuevoTemporal();
	printf("SUBS %s, %s, %s\n",identificador1,identificador2,salida);
	return salida;
}
char* multiplicar(char *identificador1, char *identificador2){
	char* salida;
	salida = nuevoTemporal();
	printf("MULT %s, %s, %s\n",identificador1,identificador2,salida);
	return salida;
}
char* dividir(char *identificador1, char *identificador2){
	char* salida;
	salida = nuevoTemporal();
	printf("DIV %s, %s, %s\n",identificador1,identificador2,salida);
	return salida;
}

