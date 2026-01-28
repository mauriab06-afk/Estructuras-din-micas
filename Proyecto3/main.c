#include <stdio.h>
#include "archivoCuentas.h"
#include "estructuraCuenta.h"
#include "listaCuentas.h"
#include "opciones.h"

int menu(void);
int menuCuenta(char usuario[]);
int menuCuentaAhorros(char usuario[]);

int main(void){
    int op,op2,op3;
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
            actualizarArchivoCuentas(frente);
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
                            fprintf(stdout,"Deposito realizado con exito\n");
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
                        }else if(op2 == 5){ //Donar dinero
                            if(donar(cuentaAct->cuenta) == ERROR){
                                fprintf(stdout,"No se pudo donar la cantidad deseada\n");
                            }else{
                                fprintf(stdout,"Gracias por su donacion\n");
                            }
                        }else if(op == 6){ //Cuenta de ahorros
                            do{
                                op3 = menuCuentaAhorros(cuentaAct->personal->usuario);
                                if(op3 == 1){ //Depositar de cuente corriente a cuenta de ahorros
                                    if(depositarCuentaAhorros(cuentaAct->cuenta) == ERROR){
                                        fprintf(stdout,"Cantidad insuficiente en cuenta corriente\n");
                                    }else{
                                        fprintf(stdout,"Cantidad depositada\n");
                                    }
                                }else if(op3 == 2){ //Retirar de cuenta de ahorros a cuenta corriente
                                    if(retirarCuentaAhorros(cuentaAct->cuenta) == ERROR){
                                        fprintf(stdout,"Cantidad insuficiente en cuenta de ahorros\n");
                                    }else{
                                        fprintf(stdout,"Cantidad retirada\n");
                                    }
                                }else if(op3 < 1 || op3 > 3){ //Opcion invalida
                                    fprintf(stdout,"Opcion invalida");
                                }
                            }while(op3 != 3);
                        }
                        if(op2 < 1 || op2 > 7){
                            fprintf(stdout,"Opcion invalida\n");
                        }
                        guardarEstadoCuentas(&cuentaAct);
                    }while(op2 != 7);
                }else{ //Nip no coincide
                    fprintf(stderr,"NIP invalido\n");
                }
            }else{ //Cuenta no encontrada
                fprintf(stderr,"Cuenta no encontrada\n");
            }
        }else if(op == 3){
            fprintf(stdout,"Eliminar cuenta\n")
        }
    }while(op != 4);
}

int menu(void){
    int n;
    fprintf(stdout,"BanMau:\n");
    fprintf(stdout,"1. Crear cuenta\n");
    fprintf(stdout,"2. Acceder a cuenta\n");
    fprintf(stdout,"3. Eliminar cuenta\n");
    fprintf(stdout,"4. Salir\n");
    fprintf(stdout,"Ingresar: ");
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
    fprintf(stdout,"5. Donar\n");
    fprintf(stdout,"6. Cuenta de ahorros\n");
    fprintf(stdout,"7. Salir\n");
    fprintf(stdout,"Ingresar: ");
    fscanf(stdin,"%d", &n);
    return n;
}

int menuCuentaAhorros(char usuario[]){
    int n;
    fprintf(stdout,"Cuenta ahorros: %s\n", usuario);
    fprintf(stdout,"1. Depositar\n");
    fprintf(stdout,"2. Retirar\n");
    fprintf(stdout,"3. Regresar\n");
    fprintf(stdout,"Ingresar: ");
    fscanf(stdout,"%d", &n);
    return n;
}
