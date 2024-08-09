CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -pedantic
OBJ = main.o tabla.o conversion.o
TARGET = tabla_de_equivalencias

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

main.o: main.c tabla.h
	$(CC) $(CFLAGS) -c main.c

tabla.o: tabla.c conversion.h tabla.h
	$(CC) $(CFLAGS) -c tabla.c

conversion.o: conversion.c conversion.h
	$(CC) $(CFLAGS) -c conversion.c

clean:
	rm -f $(OBJ) $(TARGET)


.PHONY: clean