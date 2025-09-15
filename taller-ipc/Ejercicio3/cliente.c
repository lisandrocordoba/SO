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

        // Si el usuario escribe "exit", cierro el cliente
        if(strcmp(expresion, "exit") == 0) {
            printf("Cerrando el cliente.\n");
            close(server_socket);
            exit(EXIT_SUCCESS);
        }


		// Primero le mando al servidor el tamaño de la expresión
		int expr_size = strlen(expresion) + 1; // +1 para el '\0'
		send(server_socket, &expr_size, sizeof(int), 0);

		// Luego le mando la expresión
		send(server_socket, expresion, expr_size, 0);

        // Espero el resultado del servidor
        int result;
        recv(server_socket, &result, sizeof(int), 0);
        printf("El resultado de la expresión %s es: %d\n", expresion, result);

	}
}
