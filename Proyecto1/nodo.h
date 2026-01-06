//Definimos la estructura del dodo

#ifndef NODO_H
#define NODO_H

typedef struct nodo{
    int num;
    struct nodo* sig;
    struct nodo* ant;
}NODO;

#endif
