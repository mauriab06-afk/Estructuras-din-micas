#include <stdio.h>
#include <stdlib.h>
#include "estructuraCuenta.h"



int leerEstadoCuentas(CUENTA** ubicacion){
    char archivo[100];
    FILE* fr;
    sprintf(archivo, "%s.bin", (*ubicacion)->personal->usuario);
    fr = fopen(archivo,"rb");
    if(fr == NULL){ //No se pudo abrir el archivo
        return ARCHIVO_ERROR;
    }
    (*ubicacion)->cuenta = malloc(sizeof(ESTADO));
    if((*ubicacion)->cuenta == NULL){ //No se pudo reservar la memoria
        fclose(fr);
        return ERROR;
    }
    fread((*ubicacion)->cuenta, sizeof(ESTADO), 1, fr);
    fclose(fr);
    return OK;
}

int guardarEstadoCuentas(CUENTA** ubicacion){
    char archivo[100];
    FILE* fw;
    sprintf(archivo, "%s.bin", (*ubicacion)->personal->usuario);
    fw = fopen(archivo,"wb");
    if(fw == NULL){
        return ARCHIVO_ERROR;
    }
    fwrite((*ubicacion)->cuenta, sizeof(ESTADO), 1, fw);
    fclose(fw);
}

int leerArchivoCuentas(CUENTA** frente, CUENTA** final){
    INFO* cuenta;
    INFO leido;
    CUENTA* nueva;
    FILE* fr = fopen("cuentas.bin", "rb");
    if(fr == NULL){
        return -1; //Error al abrir el archivo
    }
    while(fread(&leido, sizeof(INFO), 1, fr ) == 1){
        nueva = malloc(sizeof(CUENTA));
        if(nueva == NULL){
            fclose(fr);
            return ERROR; //No se pudo reservar memoria
        }
        cuenta = malloc(sizeof(INFO));
        if(cuenta == NULL){
            free(nueva);
            fclose(fr);
            return ERROR; //No se pudo reservar la memoria
        }
        *cuenta = leido;
        nueva->sig = NULL;
        nueva->ant = NULL;
        nueva->personal = cuenta;
        if(*frente == NULL && *final == NULL){
            *frente = nueva;
            *final = nueva;
        }else{
            nueva->ant = *final;
            (*final)->sig = nueva;
            *final = nueva;
        }
    }
    fclose(fr);
    return OK;
}

int actualizarArchivoCuentas(CUENTA* frente){
    FILE* fw = fopen("cuentas.bin", "wb");
    if(fw == NULL){
        return ARCHIVO_ERROR;
    }
    while(frente != NULL){
        fwrite(frente->personal, sizeof(INFO), 1, fw);
        frente = frente->sig;
    }
    fclose(fw);
    return OK;
}