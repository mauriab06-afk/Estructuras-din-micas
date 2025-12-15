#include <stdio.h>
#include <stdlib.h>

typedef struct nodo{
    int num;
    struct nodo* sig;
}NODO;

void menu(void);
NODO* leerArchivo(int* numElementos);
void imprimirLista(NODO* cabeza);
void agregarLista(NODO** cabeza);
void eliminarLista(NODO** cabeza);

int main(void){
    int numElementos = 0;
    int eleccion;
    NODO* cabeza;
    cabeza = leerArchivo(&numElementos); //Leemos el archivo y guardamos el numero de elementos
    fprintf(stdout,"El archivo tiene: %d elementos\n", numElementos);
    do{
        menu();
        fscanf(stdin,"%d",&eleccion);
        if(eleccion == 1){
           imprimirLista(cabeza);
        }
        if(eleccion == 2){
            agregarLista(&cabeza);
        }
        if(eleccion == 3){
            eliminarLista(&cabeza);
        }
        if(eleccion > 4 || eleccion < 1){
            fprintf(stdout,"No es una opcion valida\n");
        }
    }while(eleccion != 4);
}

void eliminarLista(NODO** cabeza){
    NODO* temp; //Nodo para recorrer la lista
    NODO* anterior; //Nodo anterior al recorrido
    int num; //Numero a eliminar
    FILE* fw; //Reescribiremos el archivo
    fprintf(stdout,"Ingrese el numero a eliminar: "); //Numero a eliminar
    fscanf(stdin,"%d",&num);
    if(*cabeza == NULL){ //La lista esta vacia
        fprintf(stdout,"No hay que eliminar\n");
        return;
    }
    if((*cabeza)->num == num){ //Si el primero en la lista se tiene que eliminar
        temp = *cabeza;
        *cabeza = temp->sig;
        free(temp);
    }else{
        temp = (*cabeza)->sig;
        anterior = *cabeza;
        while(temp != NULL && temp->num != num){ //Recorremos hasta encontrar el final
            temp = temp->sig;
            anterior = anterior->sig;
        }
        if(temp == NULL){ //Si no se encontro
            fprintf(stdout,"No se encontro el numero\n");
        }else{
            anterior->sig = temp->sig;
            free(temp);
       }
    }
    fw = fopen("binario.bin","wb");
    temp = *cabeza;
    while(temp != NULL){
        fwrite(&temp->num,sizeof(int),1,fw);
        temp = temp->sig;
    }
    fclose(fw);
}

void agregarLista(NODO** cabeza){
    NODO* nuevo = malloc(sizeof(NODO)); //Nodo nuevo
    NODO* temp;
    FILE* fa = fopen("binario.bin","ab");
    fprintf(stdout,"Ingrese el numero a agregar: "); //Valor del nodo nuevo
    fscanf(stdin,"%d",&nuevo->num);
    nuevo->sig = NULL;
    fwrite(&nuevo->num, sizeof(int), 1, fa); //Agregamos al archivo binario
    fclose(fa);
    if(*cabeza == NULL){ //Revizamos que no sea el primer nodo
        *cabeza = nuevo;
    }else{
        temp = *cabeza; //Recorremos para llegar al final
        while(temp->sig != NULL){
            temp = temp->sig;
        }
        temp->sig = nuevo; //Agregamos el nodo
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

void menu(void){
    fprintf(stdout,"Opciones:\n");
    fprintf(stdout,"1. Imprimir lista\n");
    fprintf(stdout,"2. Agregar\n");
    fprintf(stdout,"3. Eliminar\n");
    fprintf(stdout,"4. Salir\n");
    fprintf(stdout,"Ingresar: ");
}