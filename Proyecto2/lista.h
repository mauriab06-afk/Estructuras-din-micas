#ifndef LISTA_H
#define LISTA_H

#include "estructuras.h"

int agregarLista(NODO** frente, NODO** final, void* datos, size_t tam);
void imprimirLista(NODO* frente, void (*imprimir)(void*));
void liberarMemoria(NODO** frente, NODO** final, void (*liberar)(void*));
void eliminarLista(NODO** frente, NODO** final, void* parametro, int (*condicion)(void*, void*), void (*liberar)(void*));

#endif