#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/wait.h>

enum { READ, WRITE };
int pipes[2];

void process_ls(){
    close(pipes[READ]);
    dup2(pipes[WRITE], STDOUT_FILENO);
    execl("/bin/sh", "sh", "-c", "ls -al", (char *) NULL);
    exit(EXIT_FAILURE); // Si execl falla
}

void process_wc(){
    close(pipes[WRITE]);
    dup2(pipes[READ], STDIN_FILENO);
    execl("/bin/sh", "sh", "-c", "wc -l", (char *) NULL);
    exit(EXIT_FAILURE); // Si execl falla   
}


int main(void) {
    // Crear pipe
    if (pipe(pipes) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    // Crear proceso hijo para ejecutar "ls -al"
    pid_t pid_ls = fork();
    if (pid_ls == -1) exit(EXIT_FAILURE);
    else if (pid_ls == 0) process_ls();
    
    // Padre
    else { 
        // Crear proceso hijo para ejecutar "wc -l"
        pid_t pid_wc = fork();
        if (pid_wc == -1) exit(EXIT_FAILURE);
        else if (pid_wc == 0) process_wc();
       
        // Padre
        else {
            close(pipes[WRITE]);
            close(pipes[READ]);
            exit(EXIT_SUCCESS);
        }
    }
    return 0;
}