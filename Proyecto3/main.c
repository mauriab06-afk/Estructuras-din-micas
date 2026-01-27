#include <stdio.h>
#include "archivoCuentas.h"
#include "estructuraCuenta.h"
#include "listaCuentas.h"
#include "opciones.h"

int menu(void);
int menuCuenta(char usuario[]);

int main(void){
    int op,op2;
    CUENTA* frente = NULL;
    CUENTA* final = NULL;
    CUENTA* cuentaAct;
    char cuenta[50];
    int nip;
    leerArchivoCuentas(&frente,&final);
    do{
        op = menu();
        if(op == 1){
            crearCuentaLista(&frente,&final);
            fprintf(stdout,"%s", frente->personal->usuario);
        }else if(op == 2){
            fprintf(stdout,"Ingrese su nombre de usuario: ");
            fscanf(stdin,"%s", cuenta);
            cuentaAct = buscarCuenta(&frente, cuenta);
            if(cuentaAct != NULL){ //Cuenta encontrada
                fprintf(stdout,"Ingrese su NIP: ");
                fscanf(stdin,"%d",&nip);
                if(nip == cuentaAct->personal->nip){ //Nip coincide con informacion
                    leerEstadoCuentas(&cuentaAct);
                    do{ //Dentro de la cuenta
                        op2 = menuCuenta(cuentaAct->personal->usuario);
                        if(op2 == 1){ //Ver estado de cuenta
                            fprintf(stdout,"Cuenta corriente: %.2f$\n", cuentaAct->cuenta->corriente);
                        }else if(op2 == 2){ //Depositar dinero
                            depositar(cuentaAct->cuenta);
                        }else if(op2 == 3){ //Retirar dinero
                            if(retirar(cuentaAct->cuenta) == ERROR){
                                fprintf(stdout,"Saldo insuficiente\n");
                            }else{
                                fprintf(stdout,"Retiro con exito\n");
                            }
                        }else if(op2 == 4){ //Prestamo
                            if(prestamo(cuentaAct->cuenta) == ERROR){
                                fprintf(stdout,"No se pudo realizar el prestamo\n");
                            }else{
                                fprintf(stdout,"Se realizo el prestamo con exito\n");
                            }
                        }
                    }while(1);
                }else{ //Nip no coincide
                    fprintf(stderr,"NIP invalido\n");
                }
            }else{ //Cuenta no encontrada
                fprintf(stderr,"Cuenta no encontrada\n");
            }
        }
    }while(1);
}

int menu(void){
    int n;
    fprintf(stdout,"BanMau:\n");
    fprintf(stdout,"1. Crear cuenta\n");
    fprintf(stdout,"2. Acceder a cuenta\n");
    fscanf(stdin,"%d", &n);
    return n;
}

int menuCuenta(char usuario[]){
    int n;
    fprintf(stdout,"Bienvenido: %s\n", usuario);
    fprintf(stdout,"1. Estado de cuenta\n");
    fprintf(stdout,"2. Depositar\n");
    fprintf(stdout,"3. Retirar\n");
    fprintf(stdout,"4. Prestamo\n");
    fscanf(stdin,"%d", &n);
    return n;
}
