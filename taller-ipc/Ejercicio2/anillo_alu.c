#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#include "constants.h"
#include <signal.h>
#include <stdbool.h>

int generate_random_number(){
	return (rand() % 50);
}

void cerrar_pipes(int pipes_hijos[][2], int cant_pipes, int pipe_a_derecha, int pipe_a_izquierda){
	close(pipes_hijos[pipe_a_derecha][PIPE_READ]);			// Cierra el read del pipe a la derecha
	close(pipes_hijos[pipe_a_izquierda][PIPE_WRITE]); 		// Cierra el write del pipe a la izquierda
	// Cierra todos los demas pipes
	for(int i = 0; i < cant_pipes; i++){
		bool es_pipe_der = (i == pipe_a_derecha);
		bool es_pipe_izq = (i == pipe_a_izquierda);
		if(!es_pipe_izq && !es_pipe_der){
			close(pipes_hijos[i][PIPE_READ]);	
			close(pipes_hijos[i][PIPE_WRITE]);		
		}
	}
}

void proceso_hijo(int indice_proc, int n, int pipes_hijos[][2], int pipe_padre[2]){
	int pipe_a_izquierda = indice_proc - 1;
	int pipe_a_derecha = indice_proc;
	if(indice_proc == 0) pipe_a_izquierda = n - 1;			// Si es el primer proceso, el pipe de la izquierda es el ultimo (es circular)
	cerrar_pipes(pipes_hijos, n, pipe_a_derecha, pipe_a_izquierda);

	// Cierra  el pipe hacia el padre
	close(pipe_padre[PIPE_READ]);
	close(pipe_padre[PIPE_WRITE]);

	// Recibe y envia el mensaje
	while(1){
		int msg;
		read(pipes_hijos[pipe_a_izquierda][PIPE_READ], &msg, sizeof(int));
		printf("El proceso: %i recibe el numero: %i por el pipe: %i\n", indice_proc, msg, pipe_a_izquierda);

		msg++;
		printf("El proceso: %i envia el numero: %i por el pipe: %i\n", indice_proc, msg, pipe_a_derecha);
		write(pipes_hijos[pipe_a_derecha][PIPE_WRITE], &msg, sizeof(int));
	}
}

void proceso_hijo_start(int indice_proc, int n, int buffer, int pipes_hijos[][2], int pipe_padre[2]){
	int pipe_a_izquierda = indice_proc - 1;
	int pipe_a_derecha = indice_proc;
	if(indice_proc == 0) pipe_a_izquierda = n - 1;			// Si es el primer proceso, el pipe de la izquierda es el ultimo (es circular)
	cerrar_pipes(pipes_hijos, n, pipe_a_derecha, pipe_a_izquierda);

	// Cierra el read del pipe hacia el padre
	close(pipe_padre[PIPE_READ]);

	// Genera random > buffer 
	int random;
	do {
		random = generate_random_number();
	} while (!(random > buffer));
	
	printf("El buffer es: %i y el numero random es: %i \n", buffer, random);

	// Empieza la ronda de comunicacion
	printf("El proceso: %i (start) envia el numero: %i por el pipe: %i\n", indice_proc, buffer, pipe_a_derecha);
	write(pipes_hijos[pipe_a_derecha][PIPE_WRITE], &buffer, sizeof(int));
	
	// Recibe y envia el mensaje
	while(1){
		int msg;
		// Recibe el mensaje del pipe de la izquierda
		read(pipes_hijos[pipe_a_izquierda][PIPE_READ], &msg, sizeof(int));
		printf("El proceso %i recibe el numero: %i por el pipe: %i\n", indice_proc, msg, pipe_a_izquierda);
		
		// Si el mensaje es mayor o igual al buffer, lo envia al padre y termin
		if(msg >= random){
			printf("El proceso %i (start) envia el resultado: %i al padre y termina por que random era: %i\n", indice_proc, msg, random);
			write(pipe_padre[PIPE_WRITE], &msg, sizeof(int));
			exit(EXIT_SUCCESS);
		}
		// Aumenta el mensaje en 1 y lo envia al pipe de la derecha
		msg++;
		printf("El proceso: %i (start) envia el numero: %i por el pipe: %i\n", indice_proc, msg, pipe_a_derecha);
		write(pipes_hijos[pipe_a_derecha][PIPE_WRITE], &msg, sizeof(int));
	}
}


int main(int argc, char **argv)
{	
	//Funcion para cargar nueva semilla para el numero aleatorio
	srand(time(NULL));

	if (argc != 4){ printf("Uso: anillo <n> <c> <s> \n"); exit(0);}

	int status, pid, n, start, buffer;
	n = atoi(argv[1]);
	buffer = atoi(argv[2]);
	start = atoi(argv[3]);

    printf("Se crearán %i procesos, se enviará el caracter %i desde proceso %i \n", n, buffer, start);

	// Creamos n pipes para la comunicacion entre n hijos
	int pipes_hijos[n][2];
	for (int i = 0; i < n; i++)
	{
		pipe(pipes_hijos[i]);
	}
	// Creamos un pipe extra para que el hijo start le mande el resultado a el padre
	int pipe_padre[2];
	pipe(pipe_padre);

	for(int i = 0; i < n; i++){
		//Crear procesos hijos
		pid = fork();
		if (pid == -1) exit(EXIT_FAILURE);
		if (pid == 0) {
			if (i == start){
				proceso_hijo_start(i, n, buffer, pipes_hijos, pipe_padre);
			}
			else proceso_hijo(i, n, pipes_hijos, pipe_padre);
		}
	}
	// Proceso padre cierra todos los pipes excepto el usado para leer del hijo start
	for (int i = 0; i < n; i++)
	{
		close(pipes_hijos[i][PIPE_READ]);
		close(pipes_hijos[i][PIPE_WRITE]);
	}
	close(pipe_padre[PIPE_WRITE]);

	// El padre lee la respuesta enviada por el proceso start muestra el resultado
	int respuesta;
	read(pipe_padre[PIPE_READ], &respuesta, sizeof(int));	
	printf("El resultado final es: %i \n", respuesta);

	// Termina con sus hijos y consigo mismo
	kill(0, SIGTERM);
}
