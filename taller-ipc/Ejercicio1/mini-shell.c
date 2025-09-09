#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include "constants.h"
#include "mini-shell-parser.c"
#include <stdbool.h>

void redirigirStandars(int pipes[][2], int count_proc, int indice_proc){
	// Redirecciono la entrada estandar al extremo de lectura del pipe a izquierda (salvo si es el primer programa)
	bool es_primer_proc = (indice_proc == 0);
	bool es_ultimo_proc = (indice_proc == count_proc - 1);
	
	if(!es_primer_proc){	
		int pipe_a_izquierda = indice_proc - 1;
		dup2(pipes[pipe_a_izquierda][PIPE_READ], STD_INPUT);	
	}
	// Redirecciono la salida estandar al extremo de escritura del pipe a derecha (salvo si es el ultimo programa)
	if(!es_ultimo_proc){
		int pipe_a_derecha = indice_proc;
		dup2(pipes[pipe_a_derecha][PIPE_WRITE], STD_OUTPUT);	
	}
}

void cerrarPipes(int pipes[][2], int count_proc, int indice_proc){
	// PREGUNTA: Estoy cerrando todos, incluso los que voy a usar, pues ya hice el dup2?
	// Esta bien o hay q dejarlo abierto?
	int pipe_a_izquierda = indice_proc - 1;
	int pipe_a_derecha = indice_proc;
	int cant_pipes = count_proc - 1;
	for(int i = 0; i < cant_pipes; i++){
		bool es_pipe_der = (i == pipe_a_derecha);
		bool es_pipe_izq = (i == pipe_a_izquierda);
		bool es_primer_proc = (indice_proc == 0);
		bool es_ultimo_proc = (indice_proc == count_proc - 1);
		if(!es_pipe_izq || !es_primer_proc){	// Evitar el caso del primer proceso (no tiene pipe a izq)
			close(pipes[i][PIPE_READ]);	
		}
		if(!es_pipe_der || !es_ultimo_proc){	// Evitar el caso del ultimo proceso (no tiene pipe a der)
			close(pipes[i][PIPE_WRITE]);
		}
	}
}

int programa_hijo(char ***progs, int indice_proc, size_t count, int pipes[][2]){
	// Redirijo los standars y cierro los pipes que no uso
	redirigirStandars(pipes, count, indice_proc);
	cerrarPipes(pipes, count, indice_proc);

	// Ejecuto el programa
	execvp(progs[indice_proc][0], progs[indice_proc]);
	exit(EXIT_FAILURE); // Si execvp falla
}


static int run(char ***progs, size_t count)
{	
	int r, status;
	
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
	int cant_pipes = count - 1;
	for (int i = 0; i < cant_pipes; i++){
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
