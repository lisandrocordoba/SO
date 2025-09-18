Sean P0, P1 y P2 tales que  
- P0 tiene ráfagas cortas de E/S a ciertos dispositivos.
- P1 frecuentemente se bloquea leyendo de la red.
- P2 tiene ráfagas prolongadas de alto consumo de CPU y luego de escritura a disco.

### a) Conviene Round Robin o prioridades?

**Round Robin**: Scheduling preemptive donde se define un quantum y a cada proceso se lo deja ejecturar ese tiempo en cada iteracion.  

Pareceria optimo en este caso pues se van a ir ejecutando los 3 a la vez, pero siempre que $P_0$ o $P_1$ se bloqueen, $P_0$ va a poder ejecutar mas intenstamente su largo computo.  
Con un quantum apropiado, podria ser eficiente.

Agregarle **prioridades**, podria ser contraproducente.  
Si $P_2$ tiene la mayor prioridad, se va a quedar ejecutando mucho tiempo y los otros dos procesos van a quedar esperando.
Dandole prioridad a $P_0$ o $P_1$ podria ser eficiente, pero no debe haber starvation pues $P_2$ no se ejecutaria nunca.
