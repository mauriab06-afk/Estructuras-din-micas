#include "lista.h"
#include "estructuras.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int agregarLista(NODO** frente, NODO** final, void* datos, size_t tam){
    NODO* nuevo = malloc(sizeof(NODO));
    if(nuevo == NULL){
        return ERROR;
    }
    nuevo->datos = malloc(tam); 
    if(nuevo->datos == NULL){
        free(nuevo);
        return ERROR;
    }
    nuevo->sig = NULL;
    nuevo->ant = NULL;
    memcpy(nuevo->datos, datos, tam); //copia los bytes requeridos
    nuevo->tam = tam;   
    if(*frente == NULL){ //Si es el primer nodo
        *frente = nuevo;
        *final = nuevo;
    }else{ //Si es el segundo o mayor nodo
        nuevo->ant = *final;
        (*final)->sig = nuevo;
        *final = nuevo;
    }
    return OK;
}

void imprimirLista(NODO* frente, void (*imprimir)(void*)){
    while(frente != NULL){
        imprimir(frente->datos);
        frente = frente->sig;
    }
}

void liberarMemoria(NODO** frente, NODO** final, void (*liberar)(void*)){
    NODO* temp;
    while(*frente != NULL){
        temp = *frente;
        *frente = (*frente)->sig;
        liberar(temp->datos);
        free(temp);
    }
    *final = NULL;
}

void eliminarLista(NODO** frente, NODO** final, void* parametro, int (*condicion)(void*, void*), void (*liberar)(void*)){
    NODO* temp = *frente;
    NODO* sig;
    while(temp != NULL){
        sig = temp->sig;
        if(condicion(parametro, temp->datos) == 1){
            if(temp == *frente && temp == *final){
                *frente = NULL;
                *final = NULL;
            }else if(temp == *frente){
                *frente = temp->sig;
                (*frente)->ant = NULL;
            }else if(temp == *final){
                (*final) = temp->ant;
                (*final)->sig = NULL;
            }else{
                temp->sig->ant = temp->ant;
                temp->ant->sig = temp->sig;
            }
            liberar(temp->datos);
            free(temp);
        }
        temp = sig;
    }
}