#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int systemCasero(char* comando){
    pid_t pid = fork();
    if (pid == 0){
        // Proceso hijo
        execl("/bin/sh", "sh", "-c", comando, (char *)NULL); 
        // Si el execl funciona bien no deberia seguir mas el hijo
        // Asique si llega aca es que hubo un error
        perror("Error al ejecutar el comando");
        exit(EXIT_FAILURE);
    }
    // Proceso padre
    int status;
    if (waitpid(pid, &status, 0) < 0) {
        perror("waitpid");
        return -1;
    }
    return 1;
}

int main(int argc, char *argv[]){
    if(argc < 2){
        printf("Uso: ./ej6 <comando>\n");
        return 1;
    }

    systemCasero(argv[1]);
    return 0;
}