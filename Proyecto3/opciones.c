#include "opciones.h"
#include "estructuraCuenta.h"
#include <stdio.h>

int retirarCuentaAhorros(ESTADO* actual){
    float cantidad;
    fprintf(stdout,"Ingrese la cantidad a retirar: ");
    fscanf(stdin, "%f", &cantidad);
    if(cantidad > actual->ahorros){
        return ERROR;
    }
    actual->ahorros -= cantidad;
    actual->corriente += cantidad;
    return OK;
}

int depositarCuentaAhorros(ESTADO* actual){
    float cantidad;
    fprintf(stdout,"Ingrese la cantidad a despositar en la cuenta de ahorros: ");
    fscanf(stdin, "%f", &cantidad);
    if(cantidad > actual->corriente){
        return ERROR;
    }
    actual->corriente -= cantidad;
    actual->ahorros += cantidad;
    return OK;
}

int donar(ESTADO* actual){
    float cantidad;
    fprintf(stdout,"Ingrese la candidad que desea donar: ");
    fscanf(stdin,"%f", &cantidad);
    if(cantidad > actual->corriente){
        return ERROR;
    }
    actual->corriente -= cantidad;
    return OK;
}

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