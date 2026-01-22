#include <stdio.h>
#include <stdlib.h>
#include "estructuras.h"
#include "archivo.h"
#include "alumno.h"

int leerArchivo(NODO** frente, NODO** final){ //Frente y final deben de ser NULL
    NODO* nuevo;
    ALUMNO* datos;
    ALUMNO temp;
    FILE* fr = fopen("Alumnos.bin","rb");
    if(fr == NULL){//No se pudo abrir el archivo
        return ARCHIVO_ERROR;
    }
    while(fread(&temp, sizeof(ALUMNO), 1, fr) == 1){
        nuevo = malloc(sizeof(NODO));
        if(nuevo == NULL){ //No se pudo asignar memoria al nodo
            fclose(fr);
            return ERROR;
        }
        datos = malloc(sizeof(ALUMNO));
        if(datos == NULL){ //Si no se le puede asignar memoria a los datos
            fclose(fr);
            free(nuevo);
            return ERROR;
        }
        *datos = temp;
        nuevo->ant = NULL;
        nuevo->sig = NULL;
        nuevo->datos = datos;
        nuevo->tam = sizeof(ALUMNO);
        if(*frente == NULL){ //Si la lista esta vacia
            *frente = nuevo;
            *final = nuevo;
        }else{
            nuevo->ant = *final;
            (*final)->sig = nuevo;
            *final = nuevo;
        }
    }
    fclose(fr);
    return OK;
}

int guardarArchivo(NODO* frente){
    FILE* fw = fopen("Alumnos.bin", "wb");
    if(fw == NULL){
        return ARCHIVO_ERROR;
    }
    while(frente != NULL){
        fwrite(frente->datos, frente->tam, 1, fw);
        frente = frente->sig;
    }
    fclose(fw);
    return OK;
}