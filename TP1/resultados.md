 1- Muestre un comando que permita compilar todo el proyecto (sin el makefile) de  
acuerdo a los lineamientos del curso (adherir estrictamente al estándar)  
  
```gcc -std=c11 -pedantic conversion.c tabla.c main.c -o tabla_de_equivalencias```  
  
----------------------------------------------------------------  
2- Compile con el comando anterior pero modifque tabla.c de modo que no incluya  
conversion.h, copie el resultado y coméntelo.  
  
Al correr el comando, me devuelve: 
``` 
    tabla.c: In function 'estructuraTabla':  
    tabla.c:11:34: warning: implicit declaration of function 'nudo_a_kilometro' [-Wimplicit-function-declaration]  
       11 |         printf("%lf\t%lf\n",nudo,nudo_a_kilometro(nudo));        
          |     
``` 
Lo que quiere decir este warning es que dentro de la funcion estructuraTabla, de tabla.c (en la linea 11), es que   
se esta invocando a la funcion `double nudo_a_kilometro(double nudo)`, que no fue declarada antes.  
La funcion esta declarada en conversion.c, pero como ahora no esta incluido su header (y por lo tanto su declaracion),   
en tabla.c no la reconoce y devuelve dicho warning (pudiendo compliar el programa pero sin que funcione).  
  
------------------------------------------------------------------  
3- De un comando que compile todos los fuentes menos tabla.c, ejecútelo, muestre el  
resultado y coméntelo.  
  
``` gcc -std=c11 -pedantic conversion.c main.c -o tabla_de_equivalencias ``` 
  
El resultado que me devuelve es:  
```
    c:/mingw/bin/../lib/gcc/mingw32/9.2.0/../../../../mingw32/bin/ld.exe: C:\Users\dibua\AppData\Local\Temp\cc3e3PRe.o:main.c:(.text+0xee):  
    undefined reference to `estructuraTabla' collect2.exe: error: ld returned 1 exit status  
```
El error es parecido al anterior: no reconoce la funcion `void estructuraTabla(double principio, double fin, double incremento)`;  
sin embargo, la diferencia esta en que si bien esta incluida en main, el modulo donde esta definida la funcion (tabla.c) no esta compilado (no va a encontrar su objeto),  
por lo que no puede implementarla  
  
--------------------------------------------------------------------  
4- Copie el comando necesario para obtener conversion.i, el archivo ya preprocesado de   
conversion.c  
  
``` gcc -std=c11 -Wall -pedantic -E conversion.c -o conversion.i ```  


