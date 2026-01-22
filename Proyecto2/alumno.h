#ifndef ALUMNO_H
#define ALUMNO_H

typedef struct alumno{
    int cuenta;
    int semestre;
    char nombre [100];
    float promedio;
}ALUMNO;

void imprimirAlumno(void* datos);
ALUMNO* leerAlumno(void);
void liberarAlumno(void* datos);
int alumnoNumCuenta(void* parametro, void* datos);

#endif