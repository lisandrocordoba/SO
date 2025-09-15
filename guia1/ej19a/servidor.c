#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <sys/un.h>

int main(void) {
    int server_socket;
    int client_socket;
    struct sockaddr_un client_addr;
    struct sockaddr_un server_addr;
    socklen_t clen = sizeof(client_addr);
    socklen_t slen = sizeof(server_addr);

    server_addr.sun_family = AF_UNIX;
    strcpy(server_addr.sun_path, "unix_socket");
    unlink(server_addr.sun_path);

    // Creo el socket
    server_socket = socket(AF_UNIX, SOCK_STREAM, 0);

    // Asigno la direccion del socket (el archivo "unix_socket")
    if (bind(server_socket, (struct sockaddr *)&server_addr, slen) == -1) {
        perror("Error");
        exit(EXIT_FAILURE);
    }

    // Escucho conexiones
    if (listen(server_socket, 5) == -1) {
        perror("Error");
        exit(EXIT_FAILURE);
    }

    // Recibo la conexion del proceso 2
    printf("Proceso 1: esperando que el proceso 2 se conecte...\n");
    client_socket = accept(server_socket, (struct sockaddr *) &client_addr, &clen);

    // Inicio la comunicacion
    int msg = 0;
    for (int i = 0; i < 2; i++) {
        send(client_socket, &msg, sizeof(msg), 0);
        printf("Proceso 1: mandé %d al proceso 2\n", msg);

        recv(client_socket, &msg, sizeof(msg), 0);
        printf("Proceso 1: recibí %d del proceso 2\n", msg);
        msg++;
    }
    close(client_socket);
    exit(EXIT_SUCCESS);
}
    


