#include <stdio.h>
#include <stdlib.h>

typedef struct nodo{
    int num;
    struct nodo* sig;
}NODO;

int buscarPosicion(NODO* cabeza, int num);
NODO* leerArchivo(int* numElementos);

int main(void){
    int numElementos;
    int num, posicion;
    NODO* cabeza = leerArchivo(&numElementos);
    fprintf(stdout,"Ingrese el numero a buscar su posicion: ");
    fscanf(stdin,"%d",&num);
    posicion = buscarPosicion(cabeza, num);
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