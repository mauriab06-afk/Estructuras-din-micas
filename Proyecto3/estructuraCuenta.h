#ifndef ESTRUCTURACUENTA_H
#define ESTRUCTURACUENTA_H

#define ERROR 0
#define OK 1
#define ARCHIVO_ERROR -1

typedef struct estado{
    float corriente;
    float ahorros;
}ESTADO;

typedef struct info{
    char usuario[50];
    int nip;
}INFO;

typedef struct cuenta{
    INFO* personal;
    ESTADO* cuenta;
    struct cuenta* sig;
    struct cuenta* ant;
}CUENTA;

#endif