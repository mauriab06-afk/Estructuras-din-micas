#include "lista.h"
#include "archivo.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdio_ext.h>

#define ERROR 0
#define ARCHIVO_ERROR -1
#define OK 1

int menu(void);

int main(void){
    NODO* frente = NULL;
    NODO* final = NULL;
    int opcion;
    int num;
    int datos = cargarLista(&frente, &final);
    if(datos == ARCHIVO_ERROR){
        fprintf(stdout,"Error al abrir el archivo\n");
        exit(1);
    }
    do{
        opcion = menu();
        if(opcion == 1){
            fprintf(stdout,"Ingrese el numero a agregar: ");
            if(fscanf(stdin, "%d", &num) != 1){
                fprintf(stdout,"Numero invalido\n");
                __fpurge(stdin);
            }else{
                if(agregarFinal(&frente, &final, num) == OK){
                    fprintf(stdout, "Se agrego el numero a la lista\n");
                }else{
                    fprintf(stdout,"No se pudo agregar el numero a la lista\n");
                }
            }
        }
        if(opcion == 2){
            fprintf(stdout,"Ingrese el numero a eliminar: ");
            if(fscanf(stdin, "%d", &num) != 1){
                fprintf(stdout,"Numero invalido\n");
                __fpurge(stdin);
            }else{
                if(eliminarNum(&frente, &final, num) == OK){
                    fprintf(stdout, "Se elimino el numero a la lista\n");
                }else{
                    fprintf(stdout,"No se pudo eliminar el numero de la lista\n");
                }
            }
        }
        if(opcion == 3){
            imprimirDesdeFrente(frente);
        }
        if(opcion == 4){
            imprimirDesdeFinal(final);
        }
        if(opcion == 5){
            if(guardarLista(frente) != ARCHIVO_ERROR){
                fprintf(stdout,"Se guardo la lista correctamente en el archivo\n");
            }else{
                fprintf(stdout,"No se pudo guardar la lista en el archivo\n");
            }
        }
        if(opcion > 6 || opcion < 1){
            fprintf(stdout,"No es una opcion valida");
        }
    }while(opcion != 6);
    eliminarLista(&frente, &final);
}

int menu(void){
    int opcion;
    fprintf(stdout,"1. Agregar numero al final\n");
    fprintf(stdout,"2. Eliminar numero\n");
    fprintf(stdout,"3. Imprimir desde el frente\n");
    fprintf(stdout,"4. Imprimir desde el final\n");
    fprintf(stdout,"5. Guardar en archivo\n");
    fprintf(stdout,"6. Salir\n");
    fprintf(stdout, "Ingresar: ");
    if(fscanf(stdin,"%d",&opcion) == OK){
        return opcion;
    }else{
        return ERROR;
    }
}