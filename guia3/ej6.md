Count debe ser declarado atomico en memoria compartida, para que el read , el add y el write no puedan ser interrumpidos.
```c
atomic<int> count;
count.set(0);
```

Luego, el codigo quedaria asi:
```c
preparado()
count.getAndInc();

while(1)
    if (count.getAndAdd(0) == n) break;

critica();
```
Cada proceso incrementa count de forma atomica y luego se queda en un loop infinito hasta que count llegue a n, es decir hasta que todos los procesos hayan ejecutado preparado().

### a)
Es mas legible y facil de entender el codigo con atomic, ya que no hay que preocuparse por la lógica de los semaforos.

### b)

Es mas eficiente el codigo con semaforos pues el atomic genera busy waiting ya que requiere que los procesos se queden en un while(1) gastando CPU innecesariamente.

### c)

La solucion con atomic requiere soporte del HW, ya que debe asegurar que las operaciones getAndInc y getAndAdd sean atomicas.

La solucion con semaforos requiere soporte del SO, ya que el scheduler debe ser capaz de encolar los procesos que hacen wait y despertarlos cuando otro proceso hace signal.