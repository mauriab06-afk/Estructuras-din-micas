#ifndef ARCHIVOCUENTAS_H
#define ARCHIVOCUENTAS_H

#include "estructuraCuenta.h"

int leerArchivoCuentas(CUENTA** frente, CUENTA** final);
int actualizarArchivoCuentas(CUENTA* frente);
int leerEstadoCuentas(CUENTA** ubicacion);

#endif