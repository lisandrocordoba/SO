#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <string.h>
#include <sys/wait.h>


void handler_hijo(int signum){
    printf("ping, pid: %d\n", getpid());
    kill(getppid(), SIGUSR1); //envia la señal al padre
}


void handler_padre(int signum){
    printf("pong, pid: %d\n", getpid());
}


void proceso_padre(pid_t pid_hijo){
    sleep(1); //espera a que el hijo asocie la señal con el handler
    signal(SIGUSR1, handler_padre); //asocia la señal con el handler
    int seguir = 1;
    while(seguir == 1){
        // itera 3 veces el ciclo ping-pong
        for(int i=0; i<3; i++){
            // envia la seañal al hijo y espera a que el hijo le responda con otra señal
            kill(pid_hijo, SIGUSR1);
            pause();               
        }
        // pregunta al usuario si quiere iterar 3 veces mas o no
        printf("Deseas continuar? (1 para si/0 para no): ");
        scanf("%d", &seguir);
    }
    kill(pid_hijo, SIGTERM); // termina el proceso hijo
    exit(EXIT_SUCCESS);      // termina el proceso padre
}


int main(void) {
    pid_t pid_hijo = fork();
    if (pid_hijo == -1) exit(EXIT_FAILURE);
    
    else if (pid_hijo == 0) {
        signal(SIGUSR1, handler_hijo); //asocia la señal con el handler
        while(1);
    } 
    else {
        proceso_padre(pid_hijo);
    }
    return 0;
}