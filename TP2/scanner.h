#ifndef SCANNER_H_
#define SCANNER_H_

typedef enum {
    IDENTIFICADOR,
    CONSTANTE,
    OPERADOR,
    ASIGNACION,
    PUNTUACION,
    FDT
} Token;


typedef enum{
    Inicial ,
    ReconoceIdentificador ,
    IdentificadorReconocido ,
    ReconoceConstante ,
    ConstanteReconocida ,
    LexemaDeUnCaracter5 ,
    LexemaDeUnCaracter6 ,
    LexemaDeUnCaracter7 ,
    LexemaDeUnCaracter8 ,
    LexemaDeUnCaracter9 ,
    LexemaDeUnCaracter10 ,   //DEBE SER 5-10
    ReconociendoAsignacion ,
    AsignacionReconocida,
    FdtReconocido,
    ErrorLexico
    
}NUM_ESTADOS;

typedef enum{
    Letra,
    Digito,
    Suma,
    Resta,              
    ParentesisAbierto,
    ParentesisCerrado,
    Coma,
    PuntoYComa,
    DosPuntos,
    Igual,
    FDT,
    ESP,
    OTRO,
    Asterisco,
    Porcentaje,
    Division
}NUM_CARACTER;

typedef enum{
    Letra,
    identificadorLetra,
    identificadorDigito
}Identificador;

typedef enum {
    digito,
    constanteDigito
}constante;

typedef;
const char letra[26] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
const char digito[10] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
#endif


