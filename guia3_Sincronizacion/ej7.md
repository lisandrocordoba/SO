Supongo que cada proceso sabe su numero id (de 0 a n-1).
N e i son parametros.


### Memoria compartida
```c
mutex[N] = {0};     ## N semaforos inicializados en 0
mutex[i] = 1;       ## el iesimo proceso puede entrar
```

### Codigo de cada proceso
```c
mutex[id].wait();
    codigo_proceso();
mutex[(id+1) % n].signal();
```