#include <stdio.h>
#include <stdlib.h>

typedef struct nodo{
    int num;
    struct nodo* sig;
}NODO;

int leerArchivo(void);
void agregarArchivo(void);

int main(void)
{
    int elementos;
    int i;
    NODO* cabeza = NULL;
    NODO* nuevo;
    NODO* temp;
    FILE* fr;
    elementos = leerArchivo();
    fprintf(stdout,"En el archivo hay %d elementos\n",elementos);
    fr = fopen("binario.bin","rb");
    for(i = 1; i <= elementos; i++)
    {
        nuevo = malloc(sizeof(NODO));
        fread(&nuevo->num,sizeof(int),1,fr);
        nuevo->sig = cabeza;
        cabeza = nuevo;
    }
    temp = cabeza;
    while(temp != NULL)
    {
        fprintf(stdout,"%d\n",temp->num);
        temp = temp->sig;
    }
    fclose(fr);
}

void agregarArchivo(void){
    FILE* fa;
    int n;
    fa = fopen("binario.bin","ab");
    fprintf(stdout,"Ingrese el numero que quiera agregar: ");
    fscanf(stdin,"%d",&n);
    fwrite(&n,sizeof(int),1,fa);
    fclose(fa);
}

int leerArchivo(void){
    int elementos;
    FILE* fr, fa; //Uno para leer y el otro para escribir
    fr = fopen("binario.bin","rb");
    fseek(fr,0,SEEK_END);
    elementos = ftell(fr)/sizeof(int);
    fclose(fr); //Leimos cuantos elementos tiene el archivo
    return elementos;
}