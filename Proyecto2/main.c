#include "alumno.h"
#include "estructuras.h"
#include "archivo.h"
#include "lista.h"
#include <stdio.h>
#include <stdlib.h>

int menu(void);

int main(void){
    NODO* frente = NULL;
    NODO* final = NULL;
    ALUMNO* aux;
    int estado;
    int op;
    int numCuenta;
    estado = leerArchivo(&frente, &final);
    if(estado != OK){
        if(estado  == ERROR){
            fprintf(stderr, "Error con la memoria\n");
            return 1;
        }else if(estado == ARCHIVO_ERROR){
            fprintf(stderr,"Error al abrir el archivo (Alumnos.bin)\n");
            return 1;
        }
    }
    do{
        op = menu();
        if(op == 1){ //Agregar alumno
            aux = leerAlumno();
            if(aux != NULL){ //Tiene memoria asignada
                agregarLista(&frente, &final, aux, sizeof(ALUMNO));
                free(aux);
            }
        }else if(op == 2){ //Eliminar alumno
            fprintf(stdout,"Ingrese el numero de cuenta del alumno a eliminar: ");
            fscanf(stdin,"%d", &numCuenta);
            fprintf(stdout,"Se eliminaron %d alumnos\n",eliminarLista(&frente, &final, &numCuenta, alumnoNumCuenta, liberarAlumno));
        }else if(op == 3){ //Editar alumno
            fprintf(stdout,"Ingresa el numero de cuenta a editar: ");
            fscanf(stdin,"%d", &numCuenta);
            if(buscarLista(frente, &numCuenta, alumnoNumCuenta) == OK){
                aux = editarAlumno(numCuenta);
                if(aux != NULL){
                    editarLista(&frente, &numCuenta, alumnoNumCuenta, aux, sizeof(ALUMNO));
                    free(aux);
                }
            }else{
                fprintf(stdout,"No se encontro el alumno\n");
            }
        }else if(op == 4){
            imprimirLista(frente, imprimirAlumno);
        }else if(op == 5){
            guardarArchivo(frente);
        }
    }while(op != 6);
    liberarMemoria(&frente, &final, liberarAlumno);
    return 0;
}

int menu(void){
    int num;
    int c; //Usado para limpiar el buffer
    do{
        fprintf(stdout,"1. Agregar alumno\n");
        fprintf(stdout,"2. Eliminar alumno\n");
        fprintf(stdout,"3. Editar alumno\n");
        fprintf(stdout,"4. imprimir alumnos\n");
        fprintf(stdout,"5. Guardar cambios\n");
        fprintf(stdout,"6. Salir\n");
        fprintf(stdout,"Ingresar: ");
        if(fscanf(stdin, "%d", &num) != 1){
            while((c = getchar()) != '\n' && c != EOF); //Limpiar buffer
            fprintf(stderr,"Entrada invalida, intente denuevo\n");
        }else if(num < 1 || num > 6){
            fprintf(stderr,"Opcion inexistente\n");
        }
    }while (num < 1 || num > 6);
    return num;
}