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
    struct sockaddr_un server_addr;

    server_addr.sun_family = AF_UNIX;
    strcpy(server_addr.sun_path, "unix_socket");

    // Creo el socket
    server_socket = socket(AF_UNIX, SOCK_STREAM, 0);

    // Me conecto con el servidor
    printf("Proceso 2: me estoy conectando con el proceso 1...\n");
    if (connect(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("Error");
        exit(EXIT_FAILURE);
    }

    // Espero que se inicie la comunicacion
    int msg;
    for (int i = 0; i < 2; i++) {
        recv(server_socket, &msg, sizeof(msg), 0);
        printf("Proceso 2: recibí %d del proceso 1\n", msg);
        msg++;
        send(server_socket, &msg, sizeof(msg), 0);
        printf("Proceso 2: mandé %d al proceso 1\n", msg);
    }
    // Terminó la comunicacion
    close(server_socket);
    exit(EXIT_SUCCESS);
}