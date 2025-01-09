# Definición de compilador y opciones
CC = gcc
CFLAGS = -Wall -Wextra -std=c11
LDFLAGS = -lfl

# Archivos fuente
LEX_SRC = scanner.l
YACC_SRC = parser.y
MAIN_SRC = main.c
SYMBOL_SRC = symbol.c
SEMANTIC_SRC = semantic.c

# Archivos generados por Bison y Flex
LEX_GEN = lex.yy.c
YACC_GEN = parser.c
YACC_HDR = parser.h

# Archivos objeto
OBJ = $(YACC_GEN:.c=.o) $(LEX_GEN:.c=.o) $(MAIN_SRC:.c=.o) $(SYMBOL_SRC:.c=.o) $(SEMANTIC_SRC:.c=.o)

# Archivo ejecutable final
EXEC = mi_programa

# Regla principal: compila el ejecutable
all: $(EXEC)

# Regla para compilar el ejecutable
$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# Regla para generar el archivo de Bison
$(YACC_GEN) $(YACC_HDR): $(YACC_SRC)
	bison -d -o $(YACC_GEN) $(YACC_SRC)

# Regla para generar el archivo de Flex
$(LEX_GEN): $(LEX_SRC)
	flex -o $(LEX_GEN) $(LEX_SRC)

# Regla para compilar los archivos objeto
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Limpiar archivos generados
clean:
	rm -f $(EXEC) $(LEX_GEN) $(YACC_GEN) $(YACC_HDR) $(OBJ)
