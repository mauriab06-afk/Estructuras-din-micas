//Archivo de cabezera para las funciones para manejar la lista

#ifndef LISTA_H
#define LISTA_H

#include "nodo.h"

int agregarFinal(NODO** frente, NODO** final, int num);
int eliminarNum(NODO** frente, NODO** final, int num);
void imprimirDesdeFrente(NODO* frente);
void imprimirDesdeFinal(NODO* final);
void eliminarLista(NODO** frente, NODO** final);

#endif