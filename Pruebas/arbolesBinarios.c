#include <stdio.h>
#include <stdlib.h>

typedef struct nodo{
    int numero;
    struct nodo* der;
    struct nodo* izq;
}NODO;

NODO* crearNuevoNodo(int n);
void insertar(NODO** raiz, int n);
void imprimir(NODO* raiz);
void liberarArbol(NODO** raiz);
void eliminarNodoValor(NODO** raiz, int n);
NODO* buscarMax(NODO* raiz);

int main(void){
    NODO* raiz = NULL;
    int i = 10;
    int n = 2;
    while(i >= -10){
        insertar(&raiz,i);
        i--;
    }
    eliminarNodoValor(&raiz, n);
    imprimir(raiz);
}

void eliminarNodoValor(NODO** raiz, int n){
    NODO* extra;
    if(*raiz == NULL){
        return;
    }
    if(n < (*raiz)->numero){
        eliminarNodoValor(&(*raiz)->izq, n);
    }else if(n > (*raiz)->numero){
        eliminarNodoValor(&(*raiz)->der, n);
    }else{
        if((*raiz)->izq == NULL){
            extra = *raiz;
            *raiz = (*raiz)->der;
            free(extra);
        }else if((*raiz)->der == NULL){
            extra = *raiz;
            *raiz = (*raiz)->izq;
            free(extra);
        }else{
            extra = buscarMax((*raiz)->izq);
            (*raiz)->numero = extra->numero;
            eliminarNodoValor(&(*raiz)->izq, extra->numero);
        }
        
    }
}

NODO* buscarMax(NODO* raiz){
    while(raiz->der != NULL){
        raiz = raiz->der;
    }
    return raiz;
}


void liberarArbol(NODO** raiz){
    if(*raiz != NULL){
        liberarArbol(&(*raiz)->izq);
        liberarArbol(&(*raiz)->der);
        free(*raiz);
        *raiz = NULL;
    }
}

void imprimir(NODO* raiz){
    if(raiz != NULL){
        imprimir(raiz->izq);
        fprintf(stdout,"%d\n", raiz->numero);
        imprimir(raiz->der);
    }
}

void insertar(NODO** raiz, int n){ //Derecha = Mayor||Izquierda = menor      
    if(*raiz == NULL){
        *raiz = crearNuevoNodo(n);
        return;
    }
    //Se mueve segun el valor que contenga, hasta llegar al null e insertar un nuevo nodo (Recursividad)
    if(n < (*raiz)->numero){ //Izquierda
        insertar(&(*raiz)->izq, n);
    }
    if(n > (*raiz)->numero){ //Derecha
        insertar(&(*raiz)->der, n);
    }
    
}

NODO* crearNuevoNodo(int n){
    NODO* nuevo = malloc(sizeof(NODO));
    if(nuevo == NULL){ //No se pudo reservar la memoria
        return NULL;
    }
    nuevo->der = NULL;
    nuevo->izq = NULL;
    nuevo->numero = n;
    return nuevo;
};