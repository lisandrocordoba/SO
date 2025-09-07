#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char const *argv[]){
    int dato = 0;
    pid_t pid = fork();
    //si es-1, hubo un error
    if (pid ==-1) exit(EXIT_FAILURE);
    //si no hay error
    else if (pid == 0) {
        // pid vale 0 para el hijo
        for (int i=0; i< 3; i++) {
            dato++;
            printf("Dato hijo: %d\n", dato);
        }
    }
    else {
        // para el padre, pid = valor del process id del hijo
        for (int i=0; i< 3; i++) {
            printf("Dato padre: %d\n", dato);
            }
    }
    exit(EXIT_SUCCESS); //cada uno finaliza su proceso
 }