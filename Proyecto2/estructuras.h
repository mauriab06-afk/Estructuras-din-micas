#ifndef NODO_H
#define NODO_H

#include <stdio.h>

#define OK 1
#define ERROR 0
#define ARCHIVO_ERROR -1

typedef struct nodo{
    struct nodo* sig;
    struct nodo* ant;
    void* datos;
    size_t tam;
}NODO;

#endif