#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

int main() {
    int server_socket;
    struct sockaddr_un server_addr;

    server_addr.sun_family = AF_UNIX;
    strcpy(server_addr.sun_path, "unix_socket");

    // Creo el socket
    server_socket = socket(AF_UNIX, SOCK_STREAM, 0);

    // Me conecto con el servidor
    if (connect(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("Error");
        exit(EXIT_FAILURE);
    }

	while(1) {
		// Recibo de stdin la expresión a calcular
		printf("Ingrese una expresión (formato: int operador int, por ejemplo 10+5): ");
		char expresion[sizeof(int) + sizeof(int) + 1]; // la expresion es int operador int
		scanf("%s", expresion);
		int expr_size = strlen(expresion) + 1; // +1 para el '\0'

		// Primero le mando al servidor el tamaño de la expresión
		send(server_socket, &expr_size, sizeof(int), 0);

		// Luego le mando la expresión
		send(server_socket, expresion, expr_size, 0);
	}
}
