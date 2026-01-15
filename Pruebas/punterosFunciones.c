#include <stdio.h>

typedef int (*Operacion)(int , int);

int suma(int n, int m);
void imprimir(int b, int d, Operacion s);
int resta(int n, int m);

int main(void){
    int b = 2;
    int d = 4;
    imprimir(b,d,suma);
    imprimir(b,d,resta);
}

void imprimir(int b, int d, Operacion s){
    fprintf(stdout,"%d\n",s(b,d));
}

int resta(int n, int m){
    return n - m;
}

int suma(int n, int m){
    return n + m;
}