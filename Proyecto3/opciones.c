#include "opciones.h"
#include "estructuraCuenta.h"
#include <stdio.h>

int prestamo(ESTADO* actual){
    float prestamoMax = actual->corriente*1000;
    float prestamo;
    fprintf(stdout,"Ingrese la cantidad del prestamo: ");
    fscanf(stdin,"%f",&prestamo);
    if(prestamo <= prestamoMax){
        actual->corriente += prestamo;
        return OK;
    }else{
        return ERROR;
    }
}

int depositar(ESTADO* actual){
    float cantidad;
    fprintf(stdout,"Ingrese la cantidad a depositar: ");
    fscanf(stdin,"%f", &cantidad);
    actual->corriente += cantidad;
    return OK;
}

int retirar(ESTADO* actual){
    float cantidad;
    fprintf(stdout,"Ingrese la cantidad a retirar: ");
    fscanf(stdin,"%f", &cantidad);
    if(cantidad > actual->corriente){
        return ERROR;
    }
    actual->corriente -= cantidad;
    return OK;
}