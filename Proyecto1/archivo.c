#include "archivo.h"
#include <stdio.h>
#include <stdlib.h>

int guardarLista(NODO* frente){
    FILE *fw;
    fw = fopen("informacion.bin","wb");
    if(fw == NULL){ //Revisamos que el archivo haya abierto
        return -1;
    }
    while(frente != NULL){ //Recorremos la lista
        fwrite(&frente->num, sizeof(int), 1, fw); //Escribimos en el archivo
        frente = frente->sig; //Movemos la lista
    }
    fclose(fw);
    return 1;
}

int cargarLista(NODO** frente, NODO** final){ //Retorna el numero de datos
    FILE* fr;
    int num;
    int datos = 0;
    fr = fopen("informacion.bin", "rb");
    if(fr == NULL){
        return -1; // Archivo no existe
    }
    while(fread(&num, sizeof(int), 1, fr) == 1){ //Revisa que se pueda leer algo
        NODO* nuevo = malloc(sizeof(NODO));
        if(nuevo == NULL){ //Valida la reserva de memoria
            fclose(fr);
            return datos; // Retorna lo que ya logró cargar
        }
        nuevo->num = num;
        nuevo->sig = NULL;
        nuevo->ant = NULL;
        if(*frente == NULL){ // Primer nodo
            *frente = nuevo;
            *final = nuevo;
        }else{
            (*final)->sig = nuevo;
            nuevo->ant = *final;
            *final = nuevo;
        }
        datos++;
    }
    fclose(fr);
    return datos;
}
