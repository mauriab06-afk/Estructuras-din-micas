//Archivo de cabecera para las funciones para manejar el archivo binario

#ifndef ARCHIVO_H
#define ARCHIVO_H

#include "nodo.h"

int guardarLista(NODO* frente); //1 = Completado, 0 = Error
int cargarLista(NODO** frente, NODO** final);

#endif