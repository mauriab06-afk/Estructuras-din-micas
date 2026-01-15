#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct nodo{
    struct nodo* sig; //Apunta al proximo nodo
    struct nodo* ant; //Apunta al anterior nodo
    void* datos; //Guarda una direcccion pero no sabe de que
    size_t tam; //El tamaño en bytes
}NODO;

typedef struct{
    int cuenta;
    float promedio;
    int semestre;
}INFO;

typedef struct{
    float menor;
    float mayor;
}RANGO;

//Lista generica: En este caso solo tendrias que introducir el puntero a lo que quieres guardar y su tamaño (&data, sizeof(data))
int agregarLista(NODO** frente, NODO** final, const void* datos, size_t tam);
int liberarMemoria(NODO** frente, NODO** final, void (*liberarData)(void*));
void liberarINFO(void* datos);
void imprimirLista(NODO* frente, void(*imprimir)(const void*));
void imprimirInfo(const void* datos);
void eliminarIgual(NODO** frente, NODO** final, int (*cmp)(const void*, const void*), const void* parametro, void (*liberardata)(void*));
int cmpNumCuenta(const void* datos, const void* cuenta); //Dependiendo el numero de cuenta
int cmpMenorIgual(const void* datos, const void* promedioMinimo); //Dependiendo si es menor a el promedio
int cmpRango(const void* datos, const void* rango); //Dependiendo si esta en el rango

int main(void){
    NODO* frente = NULL;
    NODO* final = NULL;
    INFO info = {265318, 9.3, 2};
    INFO info2 = {200000, 8.9, 4};
    INFO info3 = {100001, 7.9, 4};
    RANGO a = {8,9};
    agregarLista(&frente, &final, &info, sizeof(INFO));
    agregarLista(&frente, &final, &info2, sizeof(INFO));
    agregarLista(&frente, &final, &info2, sizeof(INFO));
    agregarLista(&frente, &final, &info3, sizeof(INFO));
    imprimirLista(frente, imprimirInfo);
    eliminarIgual(&frente, &final, cmpRango, &a, liberarINFO);
    fprintf(stdout,"\n");
    imprimirLista(frente, imprimirInfo);
    liberarMemoria(&frente, &final, liberarINFO);
}



void eliminarIgual(NODO** frente, NODO** final, int (*cmp)(const void*, const void*), const void* parametro, void (*liberardata)(void*)){
    NODO* temp = *frente;
    NODO* sig;
    while(temp != NULL){
        sig = temp->sig; //Por si borras el nodo
        if(cmp(temp->datos, parametro) == 0){ //Cumple la condicion
            if(*frente == *final){ //Solo se tiene un nodo
                *frente = NULL;
                *final = NULL;
            }else if(*frente == temp){ //Es el primer nodo
                *frente = temp->sig;
                (*frente)->ant = NULL;
            }else if(*final == temp){ //Es el ultimo nodo
                *final = temp->ant;
                (*final)->sig = NULL;
            }else{
                temp->ant->sig = temp->sig;
                temp->sig->ant = temp->ant;
            }
            liberardata(temp->datos);
            free(temp);
        }
        temp = sig;
    }
}

int cmpRango(const void* datos, const void* rango){
    const INFO* info = (const INFO*) datos;
    const RANGO* ran = (const RANGO*) rango;
    if(info->promedio > ran->menor && info->promedio < ran->mayor){
        return 0;
    }else{
        return -1;
    }
}

int cmpMenorIgual(const void* datos, const void* promedioMinimo){
    const INFO* info = (const INFO*) datos;
    const float* min = (const float*) promedioMinimo;
    if(info->promedio <= *min){
        return 0;
    }else{
        return -1;
    }
}

int cmpNumCuenta(const void* datos, const void* cuenta){ //Ya que estos datos no se deben editar dentro de la funcion (const)
    const INFO* info = (const INFO*) datos;
    const int* numCuenta = (const int*)cuenta;
    if(info->cuenta == *numCuenta){
        return 0;
    }else{
        return -1;
    }
}

void imprimirLista(NODO* frente, void(*imprimir)(const void*)){
    while(frente != NULL){
        imprimir(frente->datos);
        frente = frente->sig;
    }
}

void imprimirInfo(const void* datos){
    const INFO* info = (const INFO*) datos;
    fprintf(stdout,"%d %.2f %d\n", info->cuenta, info->promedio, info->semestre);
}

int agregarLista(NODO** frente, NODO** final, const void* datos, size_t tam){ //const para que no se pueda modificar en la funcion

    NODO* nuevo = malloc(sizeof(NODO)); //Le asignamos memoria al nodo
    if(nuevo == NULL){
        return 0;
    }
    nuevo->datos = malloc(tam); //El tamaño de la informacion
    if(nuevo->datos == NULL){
        free(nuevo); //Libera la memoria que ya no usaste
        return 0;
    }
    memcpy(nuevo->datos,datos,tam);
    nuevo->tam = tam;
    nuevo->sig = NULL;
    nuevo->ant = NULL;
    if(*frente == NULL){ //Primero en la lista
        *frente = nuevo;
        *final = nuevo;
    }else{ //Si no es el primero en la lista
        nuevo->ant = *final;
        (*final)->sig = nuevo;
        *final = nuevo;
    }
    return 1;
}

int liberarMemoria(NODO** frente, NODO** final, void (*liberarData)(void*)){
    NODO* temp; //Para ir borrando sin perder la direcccion
    while(*frente != NULL){
        temp = *frente;
        *frente = (*frente)->sig;
        liberarData(temp->datos); //Elimina de la memoria los datos
        free(temp); //Elimina de la memoria el nodo
    }
    *final = NULL;
    return 1;
}

void liberarINFO(void* datos){ //Creamos la forma de libarar memoria que pasaremos como argumento
    INFO* info = (INFO*) datos;
    free(info);
}