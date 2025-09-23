## Caso a)

### Memoria compartida

Supongo que cada proceso sabe su numero id (de 0 a n-1).
```c
permisoA = sem(1)
permisoB = sem(0)
permisoC = sem(0)
```

### A():
```c
while(True){
    permisoA.wait()
        codigo_A()
    permisoB.signal()
}
```

### B():
```c
while(True){
    permisoB.wait()
        codigo_B()
    permisoC.signal()
}
```

### C():
```c
while(True){
    permisoC.wait()
        codigo_C()
    permiso_A.signal()
}
```
No hay inanicion pues siempre un proceso permitira que se ejecute el siguiente en el orden ABC.
Habria deadlock si los 3 semaforos empezaran en 0, pues ninguno saldria del wait().

## Caso b)

### Memoria compartida
```c
permisoA = sem(0)
permisoB = sem(1)
permisoC = sem(0)
ejecuciones_B = 0
```

### A():
```c
while(True){
    permisoA.wait()
        codigo_A()
        permisoB.signal()
}
```

### B():
```c
while(True){
    permisoB.wait()
        codigo_B()
        ejecuciones_B++         ## Notar no es necesario un mutex para esta variable pues solo puede acceder un proceso B a la vez al wait()
        if(ejecuciones_B < 2){
            permisoB.signal()
        } else {
            ejecuciones_B = 0
            permisoC.signal()
        }
}
```

### C():
```c
while(True){
    permisoC.wait()
        codigo_C()
        permiso_A.signal()
}
```

Tampoco tendremos inanicion, pues es lo mismo que el anterior pero con B ejecutandose 2 veces seguidas.

## Caso c)

### Memoria compartida
```c
permisoProductor = sem(1)
permisoConsumidor = sem(0)
cantidad_consumidores = 0
mutex = sem(1)   ## para proteger cantidad_consumidores
```

### A():
```c
while(True){
    permisoProductor.wait()
        producir()
        permisoConsumidor.signal()
        permisoConsumidor.signal()
}
```

### B():

```c
while(True){
    permisoConsumidor.wait()
        consumir()
        mutex.wait()
            cantidad_consumidores++
            if(cantidad_consumidores == 2){
                cantidad_consumidores = 0
                permisoProductor.signal()
            }
        mutex.signal()
}
```

### C():

```c
while(True){
    permisoConsumidor.wait()
        consumir()
        mutex.wait()
            cantidad_consumidores++
            if(cantidad_consumidores == 2){
                cantidad_consumidores = 0
                permisoProductor.signal()
            }
        mutex.signal()
}
```

No puede haber inanicion. El flujo es el siguiente:
- Comienza el ejecutando A, pues es el unico con permiso = 1.
- A produce y aumenta en 2 el permiso de los consumidores.
- B o C ejecutan (no importa cual primero). Consume y aumenta en 1 la variable cantidad_consumidores.
- El otro consumidor puede ejecutar en paralelo pues aun queda 1 permiso, pero solo puede consumir, luego se traba en el mutex.
- Cuando se libere el primer consumidor terminé se libera el mutex y el segundo consumidor puede aumentar cantidad_consumidores a 2 liberando el permiso del productor.
- Vuelve a comenzar el ciclo, nunca un proceso queda esperando indefinidamente.


## Caso c)

### Memoria compartida
```c
permisoProductor = sem(1)
permisoConsumidor = sem(0)
turnoConsumidorB = sem(2)
turnoConsumidorC = sem(1)
cantidad_consumidores = 0
mutex = sem(1)   ## para proteger cantidad_consumidores
```

### A():
```c
while(True){
    permisoProductor.wait()
        producir()
        permisoConsumidor.signal()
}
```

### B():

```c
while(True){
    turnoConsumidorB.wait()
    permisoConsumidor.wait()
        consumir()
        mutex.wait()
            cantidad_consumidores++
            if(cantidad_consumidores == 2){
                cantidad_consumidores = 0
                permisoProductor.signal()
            }
        mutex.signal()
}
```

### C():

```c
while(True){
    permisoConsumidor.wait()
        consumir()
        mutex.wait()
            cantidad_consumidores++
            if(cantidad_consumidores == 2){
                cantidad_consumidores = 0
                permisoProductor.signal()
            }
        mutex.signal()
}
```
