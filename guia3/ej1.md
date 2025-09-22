### Codigo izquierda

```c
// variables compartidas
 x = 0;

 A():
    x = x + 1;
    printf("%d", x)

 B():
    x = x + 1;
```
x = x + 1 no es una operacion atomica.  
Hay read, add y store. Puede ser interrumpida en cualquier momento.
La salida dependerá del orden en que ejecuten las instrucciones de A y B.  

Posibles salidas:
- 1     (B empieza luego de que A termine)
- 1     (A ejecuta el read antes que B llegue a ejecutar el add y el store)
- 2     (A empieza luego de que B termine)
- 2     (B ejecuta el store antes que A llegue a ejecutar el read)



### Codigo derecha

```c
// variables compartidas
 x = 0;
 y = 0;
 
 A():
    for (; x < 4; x++) {
        y = 0;
        printf("%d", x);
        y = 1;
    }

 B():
    while (x < 4) {
        if (y == 1)
        printf("a");
    }
```

Tampoco hay una unica salida posible, dependerá del scheduler.
- Siempre se imprimen los 4 numeros de x (0,1,2,3)
- Si antes de que A corra la siguiente iteracion, la CPU es entregada a B, se imprimirá una 'a' por cada numero. ("0a1a2a3a")
- Podria no imprimirse ninguna 'a' si siempre que va a correr B ve que y=0.
