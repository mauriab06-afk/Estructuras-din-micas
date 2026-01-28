#include <stdio.h>
#include "estructuraCuenta.h"
#include <stdlib.h>
#include <string.h>

CUENTA* buscarCuenta(CUENTA** frente, char usuario[50]){
    CUENTA* temp = *frente;
    while(temp != NULL){
        if(strcmp(usuario, temp->personal->usuario) == 0){
            break;
        }
        temp = temp->sig;
    }
    if(temp != NULL){
        return temp;
    }else{
        return NULL;
    }
}

INFO crearCuenta(void){
    INFO n;
    int prueba1, prueba2;
    fprintf(stdout,"Ingrese el nombre de usuario (max 40 caracteres): ");
    fscanf(stdin,"%s", n.usuario);
    do{
    fprintf(stdout,"Ingrese su NIP: ");
    fscanf(stdin, "%d", &prueba1);
    fprintf(stdout,"Repita su NIP: ");
    fscanf(stdin,"%d", &prueba2);
    if(prueba1 != prueba2){
        fprintf(stdout,"No coinciden (Intente denuevo)\n");
    }
    }while(prueba1 != prueba2);
    n.nip = prueba2;
    return n;
}

int crearArchivo(char cuenta[]){
    FILE* fw;
    ESTADO n;
    n.ahorros = 0;
    n.corriente = 0;
    char archivo[50];
    sprintf(archivo,"%s.bin", cuenta);
    fw = fopen(archivo,"wb");
    fwrite(&n, sizeof(ESTADO), 1, fw);
    fclose(fw);
}

int crearCuentaLista(CUENTA** frente, CUENTA** final){
    CUENTA* nueva = malloc(sizeof(CUENTA));
    if(nueva == NULL){
        return ERROR;
    }
    nueva->personal = malloc(sizeof(INFO));
    if(nueva->personal == NULL){
        free(nueva);
        return ERROR;
    }
    *(nueva)->personal = crearCuenta();
    crearArchivo(nueva->personal->usuario); //Creamos el archivo donde se guardara su informacion bancaria
    nueva->sig = NULL;
    nueva->ant = NULL;
    if(*frente == NULL){
        *final = nueva;
        *frente = nueva;
    }else{
        nueva->ant = *final;
        (*final)->sig = nueva;
        *final = nueva;
    }
    return OK;
}