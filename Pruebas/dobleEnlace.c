//Lista doblemente enlazada

#include <stdio.h>
#include <stdlib.h>

typedef struct nodo{
    int num;
    struct nodo* sig; //apunta al nodo siguiente
    struct nodo* ant; //apunta al nodo anterior
}NODO;

int main(void){
    NODO* frente = NULL; //inicializamos en null para evitar basura
    NODO* final = NULL;
}

void agregarNodo(NODO** frente, NODO** final, int num){
    NODO* nuevo = malloc(sizeof(NODO));
    if(nuevo == NULL) return; //Si no se puede reservar la memoria
    nuevo->num = num;
    nuevo->sig = NULL;
    nuevo->ant = NULL;
    if(*frente == NULL){ //Si la lista esta vacia
        *frente = nuevo;
        *final = nuevo;
    }else{
        (*final)->sig = nuevo;
        nuevo->ant = *final;
        *final = nuevo;
    }
}

void imprimirFinal(NODO* final){
    if(final == NULL){
        fprintf(stdout, "Lista vacia\n");
    }else{
        fprintf(stdout,"%d\n",final->num);
    }
}

void imprimirFrente(NODO* frente){
    if(frente == NULL){
        fprintf(stdout,"Lista vacia\n");
    }else{
        fprintf(stdout,"%d\n",frente->num);
    }
}

void imprimirDesdeFinal(NODO* final){
    while(final != NULL){
        fprintf(stdout,"%d\n",final->num);
        final = final->ant;
    }
}

void imprimirDesdeFrente(NODO* frente){
    while(frente != NULL){
        fprintf(stdout,"%d\n",frente->num);
        frente = frente->sig;
    }
}

void eliminarFinal(NODO** final, NODO** frente){
    NODO* temp;
    if(*final == NULL){ //Lista vacia
        fprintf(stdout,"Lista vacia\n");
        return;
    }

    temp = *final;
    
    if(*final == *frente){ //Si la lista solo tiene un nodo
       *final = NULL;
       *frente = NULL;
    }else{ //Si la lista tiene mas de un nodo
        *final = (*final)->ant;
        (*final)->sig = NULL;
    }
    free(temp);
}

int eliminarValor(NODO** final, NODO** frente, int num){
    NODO* temp = *frente;
    if(*final == NULL && *frente == NULL){ //Si la lista esta vacia
        return 0;
    }

    while(temp != NULL && temp->num != num){ //Recorremos la lista
        temp = temp->sig;
    }
    if(temp == NULL){ //Si no se encuentra el valor
        return 0;
    }
    if(temp == *final && temp == *frente){ //Si la lista solo tiene un elemento
        *frente = NULL;
        *final = NULL;
    }else if(temp == *frente){ //Si el numero esta al frente
        *frente = (*frente)->sig;
        (*frente)->ant = NULL;
    }else if(temp == *final){ //Si el numero esta al final
        *final = (*final)->ant;
        (*final)->sig = NULL;
    }else{ //Si el numero esta enmedio
        temp->ant->sig = temp->sig;
        temp->sig->ant = temp->ant;
    }
    free(temp);
    return 1;
}

int eliminarTodo(NODO** final, NODO** frente, int num){
    int contador = 0;
    while(eliminarValor(final, frente, num)){ //1 = continua, 0 = se detiene
        contador++;
    }
    return contador;  
}

void eliminarLista(NODO** final, NODO** frente){
    NODO* temp;
    while(*frente != NULL){
        temp = *frente;
        *frente = (*frente)->sig;
        free(temp);
    }
    *final = NULL;
}

int agregarPosicion(NODO** final, NODO** frente, int num, int posicion){
    //1 = completado, 0 = posicion no encontrada / memoria no reservada
    int actual = 0;
    NODO* temp = *frente;
    NODO* nuevo = malloc(sizeof(NODO));
    if(nuevo == NULL) return 0;
    nuevo->num = num;
    nuevo->sig = NULL;
    nuevo->ant = NULL;
    while(temp != NULL && actual != posicion){ //Recorremos hasta encontrar la posicion
        temp = temp->sig;                      //O el final
        actual++;
    }
    if(temp == NULL){ //Posicion no encontrada
        free(nuevo);
        return 0;
    }else if(temp == *frente && temp == *final){ //Solo hay un nodo
        temp->ant = nuevo;
        nuevo->sig = temp;
        *frente = nuevo;
        return 1;
    }else if(temp == *frente){ //Posicion del frente
        temp->ant = nuevo;
        nuevo->sig = temp;
        *frente = nuevo;
        return 1;
    }else if(temp == *final){ //Posicion final
        nuevo->sig = temp;
        nuevo->ant = temp->ant;
        temp->ant->sig = nuevo;
        temp->ant = nuevo;
        return 1;
    }else{
        nuevo->ant = temp->ant;
        nuevo->sig = temp;
        temp->ant->sig = nuevo;
        temp->ant = nuevo;
        return 1;
    }
}