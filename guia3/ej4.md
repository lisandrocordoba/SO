```c
wait(s):
    while (s <= 0):
        dormir();
    s--;

signal(s):
    s++;
    if(alguien espera por s):
        despertar a alguno;
```

Supongamos que wait(s) y signal(s) no son atomicos. 
Notar que s-- no es atomico, por lo que se compone de 3 pasos: leer s, restarle 1, escribir s.  
Nos encontramos con 2 problemas:

-   El proceso A y el proceso B quieren acceder a una seccion critica protegida por el semaforo s, que inicialmente vale 1. Si el proceso A ejecuta wait(s) va a tener acceso al recurso pues s=1, pero si antes de que guarde s = s - 1 el scheduler le da la CPU al proceso B, este tambien va a poder entrar a la seccion critica, pues s todavia vale 1.
En este caso, ambos tienen acceso a la seccion critica simultaneamente, lo cual no deberia pasar.
- El semaforo s vale 0 y el proceso A ejecuta signal(s). A guarda s++ pero antes de "despertar a alguno" el scheduler le da la CPU al proceso B. B se encontrara con s=1 y podra entrar a la seccion critica.
Luego A vuelve a ejecutar y "despierta a alguno", pero B ya esta en la seccion critica, por lo que se rompe la exclusion mutua.