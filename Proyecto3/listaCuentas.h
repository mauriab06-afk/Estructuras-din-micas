#ifndef LISTACUENTAS_H
#define LISTACUENTAS_H

#include "estructuraCuenta.h"

INFO crearCuenta(void);
int crearArchivo(char cuenta[]);
int crearCuentaLista(CUENTA** frente, CUENTA** final);
CUENTA* buscarCuenta(CUENTA** frente, char usuario[50]);

#endif