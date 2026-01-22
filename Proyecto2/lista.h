#ifndef LISTA_H
#define LISTA_H

#include "estructuras.h"

int agregarLista(NODO** frente, NODO** final, void* datos, size_t tam);
void imprimirLista(NODO* frente, void (*imprimir)(void*));
void liberarMemoria(NODO** frente, NODO** final, void (*liberar)(void*));
int eliminarLista(NODO** frente, NODO** final, void* parametro, int (*condicion)(void*, void*), void (*liberar)(void*));
int editarLista(NODO** frente, void* parametro, int (*condicion)(void*, void*), void* editado, size_t tam);
int buscarLista(NODO* frente, void* parametro, int (*condicion)(void*, void*));

#endif