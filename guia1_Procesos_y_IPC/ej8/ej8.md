El fork() se hace cuando dato = 0.  
Dato++ se ejecuta solo en el codigo del padre (pid != 0), por lo que en el proceso hijo SIEMPRE vale 0 ya que no se comparte la memoria.

El padre imprimirá 3 veces "Dato padre: 0".  
El hijo imprimirá "Dato hijo: 1", "Dato hijo: 2" y "Dato hijo: "3".

Pero no sabemos en que orden se imprimen, algunas opciones:
- Primero todo el padre y luego todo el hijo
- Primero todo el hijo y luego todo el padre
- Intercalados
- Etc.

Dependerá del scheduler y variara por cada vez que se corra.

```c
int main(int argc, char const *argv[]){
    int dato = 0;
    pid_t pid = fork();
    //si es-1, hubo un error
    if (pid ==-1) exit(EXIT_FAILURE);
    //si no hay error
    else if (pid == 0) {
        // pid vale 0 para el hijo
        for (int i=0; i< 3; i++) {
            dato++;
            printf("Dato hijo: %d\n", dato);
        }
    }
    else {
        // para el padre, pid = valor del process id del hijo
        for (int i=0; i< 3; i++) {
            printf("Dato padre: %d\n", dato);
            }
    }
    exit(EXIT_SUCCESS); //cada uno finaliza su proceso
 }
```
