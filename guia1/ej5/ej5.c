#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void bart(){
    printf("Soy Bart, mi pid es: %d y el de mi papa es: %d\n", getpid(), getppid());
    exit(EXIT_SUCCESS);
}

void lisa(){
    printf("Soy Lisa, mi pid es: %d y el de mi papa es: %d\n", getpid(), getppid());
    exit(EXIT_SUCCESS);
}

void maggie(){
    printf("Soy Maggie, mi pid es: %d y el de mi papa es: %d\n", getpid(), getppid());
    exit(EXIT_SUCCESS);
}

void homero(){
    printf("Soy Homero, mi pid es: %d y el de mi papa es: %d\n", getpid(), getppid());
    pid_t pidBart, pidLisa, pidMaggie;
    pidBart = fork();
    if (pidBart == 0){
        // Aca soy Bart
        bart();
    }
    else {
        // Aca sigo siendo Homero
        pidLisa = fork();
        if (pidLisa == 0){
            // Aca soy Lisa
            lisa();
        }
        else{
            // Aca sigo siendo Homero
            pidMaggie = fork();
            if (pidMaggie == 0){
                // Aca soy Maggie
                maggie();
            }
        }
    }
    // Aca sigo siendo Homero (los demas terminan antes de llegar aca)
    // Espero a los 3, no se en que orden terminaran
    wait(NULL);
    wait(NULL);
    wait(NULL);
    exit(EXIT_SUCCESS);
}

void abraham(){
    printf("Soy Abraham, mi pid es: %d y el de mi papa es: %d\n", getpid(), getppid());
    if (fork() == 0){
        // Aca soy Homero
        homero();
    } else{
        // Aca soy Abraham
        wait(NULL);
        exit(EXIT_SUCCESS);
    }
}

int main(){
    abraham();
    wait(NULL);
    exit(EXIT_SUCCESS);
}