#include <stdio.h>
#include <stdlib.h>

typedef struct nodo{
    int num;
    struct nodo* sig;
}NODO;

void imprimirLista(NODO* cabeza);
int buscarPosicion(NODO* cabeza, int num);
NODO* leerArchivo(int* numElementos);
void ordenarListaMayor(NODO* cabeza);

int main(void){
    int numElementos;
    int num, posicion;
    NODO* cabeza = leerArchivo(&numElementos);
    /*
    fprintf(stdout,"Ingrese el numero a buscar su posicion: ");
    fscanf(stdin,"%d",&num);
    posicion = buscarPosicion(cabeza, num);
    */
   imprimirLista(cabeza);
   ordenarListaMayor(cabeza);
   fprintf(stdout,"Se ordeno\n");
   imprimirLista(cabeza);
}

void ordenarListaMayor(NODO* cabeza){ //Ordenar de mayor a menor
    NODO* posicion = cabeza; //La posicion
    NODO* recorrido; //El recorrido
    int temporal; //Guardara temporalmente un numero
    while(posicion != NULL){
            recorrido = posicion->sig;
        while(recorrido != NULL){
            if(posicion->num < recorrido->num){                    
                temporal = posicion->num;
                posicion->num = recorrido->num;
                recorrido->num = temporal;
            }
            recorrido = recorrido->sig;
        }   
        posicion = posicion->sig;
    }
}

int buscarPosicion(NODO* cabeza, int num){
    int posicion = 1;
    while(cabeza != NULL && cabeza->num != num){
        cabeza = cabeza->sig;
        posicion++;
    }  
    if(cabeza == NULL){ //Si termino la lista no lo encontro
        return -1;
    }else{
        return posicion;
    }
    
}

void imprimirLista(NODO* cabeza){
    while(cabeza != NULL){
        fprintf(stdout,"%d\n",cabeza->num);
        cabeza = cabeza->sig; //Recorre e imprime
    }
}

NODO* leerArchivo(int* numElementos){
    FILE* fr;
    int num; //Guarda temporalmente lo leido en el binario
    NODO* cabeza = NULL;
    NODO* temp;
    fr = fopen("binario.bin","rb");
    while((fread(&num,sizeof(int),1,fr)) == 1){ //Mientras se lea un elemento sigue funcionando
        NODO* nuevo = malloc(sizeof(NODO));
        nuevo->sig = NULL;
        nuevo->num = num;
        if(cabeza == NULL){
            cabeza = nuevo;
        }else{
            temp = cabeza; //nodo para recorrer lista y agregar al final
            while(temp->sig != NULL){ //Mientras no sea el final
                temp = temp->sig; //Avanza
            }
            temp->sig = nuevo;
        }
        (*numElementos)++;
    }
    fclose(fr);
    return cabeza; //Retornamos cabeza
}