#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <string.h>
#include <sys/wait.h>

int main(void) {
    // Empieza siendo Juan
    pid_t pid_julieta = fork();
    if (pid_julieta == -1) exit(EXIT_FAILURE);
    else if (pid_julieta == 0){
        // Julieta saluda y crea a Jennifer
        printf("Soy Julieta\n");
        sleep(1);
        pid_t pid_Jennifer = fork();
        if (pid_Jennifer == -1) exit(EXIT_FAILURE);
        else if (pid_Jennifer == 0){
            // Jennifer saluda, espera 1 segundo y termina
            printf("Soy Jennifer\n");
            sleep(1);
            exit(EXIT_SUCCESS);
        }
        else{
            // Julieta termina luego de crear a Jennifer
            exit(EXIT_SUCCESS);
        }
    } 
    else {
        // Vuelve a ser Juan
        printf("Soy Juan\n");
        sleep(1);
        // Espera a que Julieta termine y crea a Jorge
        wait(NULL);             
        pid_t pid_jorge = fork();
        if (pid_jorge == -1) exit(EXIT_FAILURE);
        else if (pid_jorge == 0){
            // Jorge saluda, duerme 1 segundo y termina
            printf("Soy Jorge\n");
            sleep(1);
            exit(EXIT_SUCCESS);
        }
        else{
            // Juan termina luego de crear a Jorge
            exit(EXIT_SUCCESS);
        }
    }

    return 0;
}