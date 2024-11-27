# Definición de compilador y opciones
CC = gcc
CFLAGS = -Wall

# Archivos fuente
LEX_SRC = scanner.l
YACC_SRC = parser.y
MAIN_SRC = main.c

# Archivos generados por Bison y Flex
LEX_GEN = lex.yy.c
YACC_GEN = parser.c
YACC_HDR = parser.h

# Archivo ejecutable final
EXEC = mi_programa

# Regla principal: compila el ejecutable
all: $(EXEC)

# Regla para compilar el ejecutable
$(EXEC): $(YACC_GEN) $(LEX_GEN) $(MAIN_SRC)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(EXEC) $(YACC_GEN) $(LEX_GEN) $(MAIN_SRC) -lfl

# Regla para generar el archivo de Bison
$(YACC_GEN) $(YACC_HDR): $(YACC_SRC)
	bison -d $(YACC_SRC)

# Regla para generar el archivo de Flex
$(LEX_GEN): $(LEX_SRC)
	flex $(LEX_SRC)

# Limpiar archivos generados
clean:
	rm -f $(EXEC) $(LEX_GEN) $(YACC_GEN) $(YACC_HDR)