#ifndef OPCIONES_H
#define OPCIONES_H

#include "estructuraCuenta.h"

int depositar(ESTADO* actual);
int retirar(ESTADO* actual);
int prestamo(ESTADO* actual);
int donar(ESTADO* actual);
int depositarCuentaAhorros(ESTADO* actual);
int retirarCuentaAhorros(ESTADO* actual);

#endif