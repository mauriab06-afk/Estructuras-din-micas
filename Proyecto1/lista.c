#include "lista.h"
#include <stdio.h>
#include <stdlib.h>

int agregarFinal(NODO** frente, NODO** final, int num){
    NODO* nuevo = malloc(sizeof(NODO));
    if(nuevo == NULL){
        return 0; //No se pudo reservar memoria
    }
    nuevo->num = num;
    nuevo->sig = NULL;
    nuevo->ant = NULL;
    if(*frente == NULL){
        *frente = nuevo;
        *final = nuevo;
    }else{
        (*final)->sig = nuevo;
        nuevo->ant = *final;
        *final = nuevo;
    }
    return 1; //Se agrego a la lista
}

int eliminarNum(NODO** frente, NODO** final, int num){
    NODO* temp = *frente; //Usaremos temp para recorrer
    if(temp == NULL){ //Si la lista esta vacia
        return 0;
    }
    while(temp != NULL){ //Recorre la lista
        if(temp->num == num && temp == *frente && temp == *final){ //Unico nodo
            *frente = NULL;
            *final = NULL;
            free(temp);
            return 1;
        }else if(temp->num == num && temp == *frente){ //Primer nodo
            *frente = temp->sig;
            (*frente)->ant = NULL;
            free(temp);
            return 1;
        }else if(temp->num == num && temp == *final){ //Ultimo nodo
            *final = temp->ant;
            (*final)->sig = NULL;
            free(temp);
            return 1;
        }else if(temp->num == num){ 
            temp->ant->sig = temp->sig;
            temp->sig->ant = temp->ant;
            free(temp);
            return 1;
        }
        temp = temp->sig;
    }
    return 0; //No se encontro
}

void imprimirDesdeFrente(NODO* frente){
    while(frente != NULL){
        fprintf(stdout,"%d \n", frente->num);
        frente = frente->sig;
    }
}

void imprimirDesdeFinal(NODO* final){
    while(final != NULL){
        fprintf(stdout,"%d \n", final->num);
        final = final->ant;
    }
}

void eliminarLista(NODO** frente, NODO** final){
    NODO* temp;
    while(*frente != NULL){
        temp = *frente;
        *frente = (*frente)->sig;
        free(temp);
    }
    *final = NULL;
}