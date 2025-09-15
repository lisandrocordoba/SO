#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

void servidor_hijo();

int calcular(const char *expresion) {
    int num1, num2, resultado;
    char operador;

    // Usamos sscanf para extraer los dos números y el operador de la expresión
    if (sscanf(expresion, "%d%c%d", &num1, &operador, &num2) != 3) {
        printf("Formato incorrecto\n");
        return 0;  // En caso de error, retornamos 0.
    }

    // Realizamos la operación según el operador
    switch (operador) {
        case '+':
            resultado = num1 + num2;
            break;
        case '-':
            resultado = num1 - num2;
            break;
        case '*':
            resultado = num1 * num2;
            break;
        case '/':
            if (num2 != 0) {
                resultado = num1 / num2;
            } else {
                printf("Error: División por cero\n");
                return 0;  // Si hay división por cero, retornamos 0.
            }
            break;
        default:
            printf("Operador no reconocido\n");
            return 0;  // Si el operador no es válido, retornamos 0.
    }

    return resultado;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int client_socket;  // PREGUNTAR: Lo pongo global para que lo pueda usar el hijo. Por convencion se hace asi o pasandoselo como parametro??
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main() {
    int server_socket;
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

    printf("Servidor esperando que se conecte algun cliente...\n");
    while(1) {
        // Si recibo un cliente, creo un proceso hijo para atenderlo
        client_socket = accept(server_socket, (struct sockaddr *) &client_addr, &clen);
        pid_t pid_hijo = fork();
        if (pid_hijo == 0) {
            servidor_hijo();
        }
        close(client_socket); // El padre cierra el socket del cliente
    }
    exit(0);
}



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// PREGUNTAR: Deberia cerrar el server_socket?? El hijo ya no lo va a usar, pero lo hereda del padre.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void servidor_hijo() {
    while(1) {
        // Primero el cliente le manda el tamaño de la expresion
        int expr_size;
        if (recv(client_socket, &expr_size, sizeof(int), 0) == 0) {
            // El cliente cerro la conexion
            printf("El cliente cerró la conexión. Terminando el servidor hijo.\n");
            exit(EXIT_SUCCESS);
        }

        // Luego el cliente le manda la expresion
        char expression[expr_size + 1]; // +1 para el '\0'
        if (recv(client_socket, expression, expr_size, 0) == 0) {
            // El cliente cerro la conexion
            printf("El cliente cerró la conexión. Terminando el servidor hijo.\n");
            exit(EXIT_SUCCESS);
        }                
        expression[expr_size] = '\0';  // Aseguramos que la cadena esté terminada en null
        
        int result = calcular(expression);
        printf("Servidor calculó la expresión y envía el resultado al cliente.\n");
        send(client_socket, &result, sizeof(int), 0);
        // Al finalizar se queda esperando si llega otra expresión.
    }
}