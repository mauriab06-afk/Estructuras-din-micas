#include "opciones.h"
#include "estructuraCuenta.h"
#include <stdio.h>

int depositar(ESTADO* actual){
    float cantidad;
    fscanf(stdin,"%f", &cantidad);
    actual->corriente += cantidad;
    return OK;
}

int retirar(ESTADO* actual){
    float cantidad;
    fscanf(stdin,"%f", &cantidad);
    if(cantidad > actual->corriente){
        return ERROR;
    }
    actual->corriente -= cantidad;
    return OK;
}