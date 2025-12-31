#include <stdio.h>
#include <stdlib.h>

//Pilas

typedef struct nodo{
    int num;
    struct nodo* sig;
}NODO;

void push(NODO** cabeza, int num);
int menu(void);
void pop(NODO** cabeza);

int main(void){
    NODO* cabeza = NULL;
    int opcion;
    int num;
    do{
        opcion = menu();
        if(opcion == 1){
            fprintf(stdout,"Ingrese el numero a agregar: ");
            fscanf(stdin,"%d",&num);
            push(&cabeza,num);
        }
        if(opcion == 2){
            pop(&cabeza);
        }
        if(opcion == 3){
            if(cabeza != NULL){  //Si la lista no esta vacia
                fprintf(stdout,"Numero en el tope de la pila: %d\n", cabeza->num);
            }else{
                fprintf(stdout,"La lista esta vacia\n");
            }
        }
    }while(opcion != 4);
    while(cabeza != NULL){
        pop(&cabeza);
    }
    return 0;
}

int menu(void){
    int num;
    fprintf(stdout,"1. Agregar a la pila (push)\n");
    fprintf(stdout,"2. Eliminar de la pila (pop)\n");
    fprintf(stdout,"3. Imprimir primero en la pila\n");
    fprintf(stdout,"4. Salir\n");
    fprintf(stdout,"Ingresar: ");
    fscanf(stdin,"%d", &num);
    return num;
}

void pop(NODO** cabeza){
    NODO* temp;
    if(*cabeza != NULL){ //Si la lista no esta vacia borra el ultimo nodo agregado
        temp = *cabeza;
        *cabeza = (*cabeza)->sig;
        free(temp);
    }else{ //Si esta vacia envia este mensaje
        fprintf(stdout,"Pila vacia\n");
    }
}

void push(NODO** cabeza, int num){ //Agrega un nuevo nodo al inicio
    NODO* nuevo = malloc(sizeof(NODO));
    if(nuevo == NULL){ //Verificamos el malloc
        fprintf(stdout,"Error en memoria\n");
        return;
    }
    nuevo->num = num;
    nuevo->sig = *cabeza;
    *cabeza = nuevo;
}