#include "tabla.h"

void estructuraTabla(double principio, double fin, double incremento){
    assert(principio >= 0);
    assert(fin >= principio);
    assert(incremento > 0);

    printf("|nudos          |km/h \n");

    for(double nudo = principio ; nudo <= fin ; nudo += incremento){
        printf("|%lf\t|%lf\n",nudo,nudo_a_kilometro(nudo)); 
    }
}
