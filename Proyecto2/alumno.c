#include "alumno.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void imprimirAlumno(void* datos){
    ALUMNO* alumno = (ALUMNO*) datos;
    fprintf(stdout,"%d %d %s %.2f\n", alumno->cuenta, alumno->semestre, alumno->nombre, alumno->promedio);
}

ALUMNO* leerAlumno(void){
    ALUMNO* alumno = malloc(sizeof(ALUMNO));
    char temporal[100];
    fprintf(stdout,"Ingrese la cuenta del alumno: ");
    fscanf(stdin,"%d", &alumno->cuenta);

    fprintf(stdout,"Ingrese el semestre del alumno: ");
    fscanf(stdin,"%d", &alumno->semestre);

    getchar(); //Elimina el \n que deja el fscanf

    fprintf(stdout, "Ingrese el nombre del alumno: ");
    fgets(temporal, sizeof(temporal), stdin);
    strcpy(alumno->nombre, strtok(temporal,"\n"));

    fprintf(stdout, "Ingresa el promedio del alumno: ");
    fscanf(stdin,"%f", &alumno->promedio);
    return alumno;
}

void liberarAlumno(void* datos){
    ALUMNO* temp = (ALUMNO*) datos;
    free(temp);
}

int alumnoNumCuenta(void* parametro, void* datos){
    int* numCuenta = (int*) parametro;
    ALUMNO* alumno = (ALUMNO*) datos;
    if(alumno->cuenta == *numCuenta){
        return 1;
    }else{
        return 0;
    }
}