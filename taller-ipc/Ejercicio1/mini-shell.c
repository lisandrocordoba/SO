#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include "constants.h"
#include "mini-shell-parser.c"


int programa_hijo(char ***progs, int i, size_t count, int pipes[][2]){
	// Si es el primer programa, solo redirecciono la salida estandar al pipe a la derecha ##############	CREO QUE ESTA ##############
	// Si es el ultimo programa, solo redirecciono la entrada estandar al pipe a la izquierda ############## CREO QUE ESTA ##############
	// Si es un programa intermedio, redirecciono la entrada estandar al pipe a la izquierda y la salida estandar al pipe a la derecha

	// Cierro los pipes que no son del iesimo proceso y redirecciono los que si 
	for(int j = 0; j < count - 1; j++){
		if(j == i - 1){
			close(pipes[j][PIPE_WRITE]);			// Cierro el extremo de escritura del pipe a izquierda
			dup2(pipes[j][PIPE_READ], STD_INPUT);	// Redirecciono la entrada estandar al extremo de lectura del pipe a izquierda
			//printf("Soy [%s], mi pid es [%d], redirijo el STDINPUT a pipe[%d]\n", progs[i][0],getpid(), j);
		}
		else if(j == i){
			close(pipes[j][PIPE_READ]);				// Cierro el extremo de lectura del pipe a derecha
			//printf("Soy [%s], redirijo el STDOUTPUT a pipe[%d]\n", progs[i][0], j);
			dup2(pipes[j][PIPE_WRITE], STD_OUTPUT);	// Redirecciono la salida estandar al extremo de escritura del pipe a derecha
			//printf("LLEGUE A DUP2\n");
		}
		else{
			// Cierro ambos extremos de los demas pipes
			close(pipes[j][PIPE_READ]);				
			close(pipes[j][PIPE_WRITE]);
		}
	}
	execvp(progs[i][0], progs[i]);
	exit(EXIT_FAILURE); // Si execvp falla
}


static int run(char ***progs, size_t count)
{	
	int r, status;
	//printf("El pid padre es [%d]\n", getpid());

	//Reservo memoria para el arreglo de pids
	pid_t *children = malloc(sizeof(*children) * count);

	// Necesito count-1 pipes, uno entre cada par de programas a ejecutar
	int pipes[count-1][2];
	for (int i = 0; i < count-1; i++){
		if (pipe(pipes[i]) == -1) {
			perror("pipe");
			exit(EXIT_FAILURE);
		}
	}
	// Necesito count procesos, uno para cada programa a ejecutar
	for (int i = 0; i < count; i++){
		// Creo el i-esimo proceso
		children[i] = fork();
		if (children[i] == -1) exit(EXIT_FAILURE);
		else if (children[i] == 0) programa_hijo(progs, i, count, pipes); // El proceso necesita saber que programa es y que pipe le corresponde
	}
	// El padre cierra los pipes, pues no los va a usar. Hay que cerrarlos despues del for, porque si no los hijos heredan los descriptores cerrados
	for (int i = 0; i < count; i++){
		close(pipes[i][PIPE_WRITE]);
		close(pipes[i][PIPE_READ]);
	}

	//Espero a los hijos y verifico el estado que terminaron
	for (int i = 0; i < count; i++) {
		waitpid(children[i], &status, 0);

		if (!WIFEXITED(status)) {
			fprintf(stderr, "proceso %d no terminó correctamente [%d]: ",
			    (int)children[i], WIFSIGNALED(status));
			perror("");
			return -1;
		}
	}
	r = 0;
	free(children);

	return r;
}


int main(int argc, char **argv)
{
	if (argc < 2) {
		printf("El programa recibe como parametro de entrada un string con la linea de comandos a ejecutar. \n"); 
		printf("Por ejemplo ./mini-shell 'ls -a | grep anillo'\n");
		return 0;
	}
	int programs_count;
	char*** programs_with_parameters = parse_input(argv, &programs_count);

	printf("status: %d\n", run(programs_with_parameters, programs_count));

	fflush(stdout);
	fflush(stderr);

	return 0;
}
