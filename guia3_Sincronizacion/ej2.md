```c
x = 0; // Variable compartida
mutex(1); // Mutex compartido

while (1) {
    mutex.wait();
        y = x; // Lectura de x
    mutex.signal();
    if (y <= 5) {
        x++;
    } else {
        x--;
    }
}
```

Hay race condition, el mutex deberia proteger tanto la lectura como la escritura de x.
Supongamos que dos procesos quieren leer x al mismo tiempo. No lo van a poder hacer gracias al Mutex, pero el 2° va a poder leerlo antes de que el 1° lo modifique. Entonces ambos procesos van a leer el mismo valor de x.