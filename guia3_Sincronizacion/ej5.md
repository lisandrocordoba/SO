```c
preparado()

mutex.wait()
count = count + 1
mutex.signal()

if (count == n)
    barrera.signal()

barrera.wait()

critica()
```
Hay inanicion porque correrá el signal de la barrera solo el ultimo proceso que llegue a esa linea (solo ahi count == n). Por lo que habrá 1 solo "permiso" para la barrera (suponiendo que se inicializa en 0) pero N procesos que quieren utilizarlo. Los n-1 procesos restantes quedarán esperando indefinidamente.

### Una forma de solucionarlo

Reemplazar 

```c
barrera.signal()
```

por

```c
for (int i = 0; i < n; i++) barrera.signal()
```

De esta forma, habra 1 permiso para cada proceso que llegue a la barrera.

### Otra forma de solucionarlo

Reemplazar

```c
barrera.wait()

critica()
```

por

```c
else{
    barrera.wait()
    barrera.signal()
    critica()
}
```

De esta forma, el ultimo proceso (el que vea que count == n) hace 1 signal permitiendo que alguno de los que estan esperando en la barrera pueda continuar. Ese proceso que continua hace otro signal, y asi sucesivamente hasta que todos hayan pasado.