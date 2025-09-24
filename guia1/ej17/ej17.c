#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/wait.h>

enum  { READ, WRITE };

int calculoTerminado;

void handler(int sig){
    calculoTerminado = 1;
}

void ejecutarNieto(int numero, int pipe[2]){
    int resultado = calcular(numero);
    close(pipe[WRITE]);
    write(pipe[WRITE], &resultado, sizeof(resultado));
    kill(getppid(), SIGUSR1);
    exit(0);
}

void ejecutarHijo (int i, int pipes[][2]) {
    // Handleo la señal para que el nieto avise cuando termina el calculo
    signal(SIGUSR1, handler);

    // Cerrar pipes
    for (int j = 0; i < N; i++){
        if (j == i){
            close(pipes[j][WRITE]);     // Cierra extremo de escritura del primer pipe con el padre
            close(pipes[N+j][READ]);    // Cierra extremo de lectura del segundo pipe con el padre
        } else{
            // Cierra todos los demas pipes 
            close(pipes[j][READ]);
            close(pipes[j][WRITE]);
            close(pipes[N+j][READ]);
            close(pipes[N+j][WRITE]);
        }
    }

    // Creo el pipe para la comunicacion con el nieto
    int pipe_nieto[2];
    pipe(pipe_nieto);

    // Leer numero
    int numero;
    read(pipes[i][READ], &numero, sizeof(numero));

    // Crear nieto
    pid_t nieto = fork();
    if (nieto == 0){
        ejecutarNieto(numero, pipe_nieto);
        exit(0);
    } else{

    }
    // Responder al polling
    char termine;
    while(!calculoTerminado){
        // Leo el polling del padre
        read(pipes[i][READ], &termine, sizeof(termine));
        // Si el calculo ya termino, aviso al padre y corto el loopq
        if(calculoTerminado){
            termine = 1;
            write(pipes[N+i][WRITE], &termine, sizeof(termine));
            break;
        }
        // Si no termino, aviso al padre que no termine
        write(pipes[N+i][WRITE], &termine, sizeof(termine));
    }
    // Leer resultado del nieto
    int resultado;
    read(pipe_nieto[READ], &resultado, sizeof(resultado));
    
    // Avisar al padre el resultado
    write(pipes[N+i][WRITE], &numero, sizeof(numero));
    write(pipes[N+i][WRITE], &resultado, sizeof(resultado));
    wait(NULL);

}


int main(int argc, char* argv[]){
    if (argc< 2) {
        printf ("Debe ejecutar con la cantidad de hijos como parametro\n");
        return 0;
    }
    int N = atoi(argv[1]);

    int pipes[N*2][2];
    for ( int i=0; i< N*2; i++){
        pipe(pipes[i]);
    }

    for (int i=0; i< N; i++) {
        int pid = fork ();
        if (pid==0) {
            ejecutarHijo(i,pipes);
            return 0;
        } else {
            int numero = dameNumero(pid) ;
            write(pipes[i][1], &numero, sizeof(numero));
        }
    }

    int cantidadTerminados = 0;
    char hijoTermino[N] = {0};
    while (cantidadTerminados < N) {
        for ( int i=0; i< N; i++) {
            if (hijoTermino[i]) continue;
            char termino = 0;
            write(pipes[i][1], &termino, sizeof(termino));
            read(pipes[N+i][0], &termino, sizeof(termino));
            if (termino) {
                int numero;
                int resultado ;
                read(pipes[N+i][0], &numero, sizeof(numero));
                read(pipes[N+i][0], &resultado, sizeof(resultado));
                informarResultado(numero, resultado);
                hijoTermino[i] = 1;
                cantidadTerminados++;
            }
        }
    }   
    wait(NULL);
    return 0;
}