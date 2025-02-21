# Transcompilador de mini a C

Este repositorio contiene el trabajo práctico desarrollado para la asignatura **Sintaxis y Semántica de los Lenguajes** (k2002) en la UTN - Facultad Regional de Buenos Aires, bajo la supervisión del Prof. Eduardo Zuñiga durante el año 2024.

## Descripción

El proyecto consiste en la implementación de un **transcompilador** que traduce código escrito en el lenguaje **mini** a código en **C**. Para ello se han desarrollado los siguientes componentes:

- **Scanner**: Implementado en Flex, encargado de analizar y tokenizar la entrada.
- **Parser**: Implementado en Bison, encargado de analizar la estructura sintáctica y construir el flujo de traducción.

El objetivo del proyecto es afianzar los conocimientos en análisis semantico, léxico y sintáctico, así como en la construcción de un transcompilador.

## Contenido del Repositorio

- `scanner.l`: Código fuente del scanner en Flex.
- `parser.y`: Código fuente del parser en Bison.
- `main.c`: Programa principal que integra los componentes del transcompilador.
- `Makefile`: Archivo de compilación para generar el ejecutable.
- Otros archivos y documentación complementaria.

## Requisitos

- GNU Flex
- GNU Bison
- Compilador de C (gcc)
- Make

## Instrucciones de Compilación y Ejecución

1. **Clonar el repositorio:**
   ```bash
   git clone <URL_DEL_REPOSITORIO>

2. **Compilar el proyecto usando make:**
   ```bash
    make

3. **Ejecutar el transcompilador redireccionando un archivo de entrada**
   ```bash
    ./mini < archivo_de_entrada.txt

## Autor
**Manuel Di Bucci**

## Asignatura
**Sintaxis y Semántica de los Lenguajes (k2002)**  
UTN - Facultad Regional de Buenos Aires  
Año 2024

## Profesor
**Prof. Eduardo Zuñiga**

## Licencia
Este proyecto es de uso académico y se distribuye con fines educativos.


