#include <stdio.h>
#include <stdlib.h>

//Primero en entrar, primero en salir

typedef struct nodo{
    int num;
    struct nodo* sig;
}NODO;

void agregar(NODO** frente, NODO** final, int num); //Agregar a la lista con el valor que le des
void eliminar(NODO** frente, NODO** final); //Elimina el frente de la lista (Primer valor)
void imprimirTodo(NODO* frente); //Imprime toda la lista
void eliminarLista(NODO** frente, NODO** final); //Borra toda la lista
int menu(void);

int main(void){
    NODO* frente = NULL; //Apuntara al primer elemento agregado
    NODO* final = NULL; //Apuntara al ultimo nodo
    int eleccion, num;
    do{
        eleccion = menu();
        if(eleccion == 1){
            fprintf(stdout,"Ingrese el numero a añadir: ");
            fscanf(stdin,"%d",&num);
            agregar(&frente, &final, num);
        }
        if(eleccion == 2){
            eliminar(&frente, &final);
        }
        if(eleccion == 3){
            if(frente != NULL){
                fprintf(stdout,"%d\n", frente->num);
            }else{
                fprintf(stdout,"Lista vacia\n");
            }
        }
        if(eleccion == 4){
            imprimirTodo(frente);
        }
        if(eleccion == 5){
            eliminarLista(&frente, &final);
        }
        if(eleccion < 1 || eleccion > 6){
            fprintf(stdout,"Eleccion invalida\n");
        }
    }while(eleccion != 6);
}

void eliminarLista(NODO** frente, NODO** final){
    while(*frente != NULL){
        eliminar(frente, final);
    }
}

void imprimirTodo(NODO* frente){
    NODO* temp = frente;
    while(temp != NULL){
        fprintf(stdout,"%d\n",temp->num);
        temp = temp->sig;
    }
}

int menu(void){
    int num;
    fprintf(stdout,"Menu:\n");
    fprintf(stdout,"1. Agregar\n");
    fprintf(stdout,"2. Eliminar frente\n");
    fprintf(stdout,"3. Imprimir frente\n");
    fprintf(stdout,"4. Imprimir todo\n");
    fprintf(stdout,"5. Eliminar lista\n");
    fprintf(stdout,"6. Salir\n");
    fprintf(stdout,"Ingresar: ");
    fscanf(stdin,"%d",&num);
    return num;
}

void agregar(NODO** frente, NODO** final, int num){
    NODO* nuevo = malloc(sizeof(NODO));
    nuevo->num = num;
    nuevo->sig = NULL;
    if(*frente == NULL){ //Si es el primer nodo
        *final = nuevo;
        *frente = nuevo;
    }else{ //Si no
        (*final)->sig = nuevo;
        *final = nuevo;
    }
}

void eliminar(NODO** frente, NODO** final){
    NODO* temp = *frente;
    if(*frente != NULL){ //Si la lista no esta vacia
        *frente = (*frente)->sig;
        free(temp);
    }
    if(*frente == NULL){ //Si no hay nada mas enfrente
        *final = *frente;
    }
}

