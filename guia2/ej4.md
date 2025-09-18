### a) Round-robin
No puede producir starvation(inanición) pues todo los procesos ejecutan el quantum definido y se entrega la CPU al siguiente proceso en la cola.  
### b) Por prioridad
Puede producir starvation si constantemente llegan procesos de alta prioridad o si estos demoran mucho tiempo en ejecutarse. De esta manera los de baja prioridad pueden quedar esperando indefinidamente.  
### c) Shortest Job First (SJF)
Es un caso particular del de prioridad, por lo que también puede provocar starvation si constantemente llegan procesos con bajo tiempo de ejecución.
### d) Shortest Remaining Time First (SRTF)
Es SJF con la diferencia de que en este caso se puede interrumpir un proceso en ejecución si llega otro proceso con menor tiempo de ejecución. Al igual que SJF, puede provocar starvation si constantemente llegan procesos con menor tiempo de ejecución.
### e) FIFO
No puede producir starvation pues los procesos se ejecutan hasta su finalización en el orden en que llegaron. Eventualmente a todos los procesos les tocará su turno.
### f) Multilevel Queue
Al utilizar prioridad, puede producir starvation si constantemente llegan procesos de alta prioridad.
### g) Multilevel Feedback Queue (aging)
No hay starvation entre colas pues utiliza aging, lo que hace que los procesos que llevan mucho tiempo esperando vayan aumentando dependiendo el criterio dentro de cada cola puede haber starvation.  
Sin embargo, dependiendo el criterio que se utilice dentro de cada cola, puede haber starvation. Por ejemplo, si en la de maxima prioridad se utiliza SJF y constantemente llegan procesos con bajo tiempo de ejecución, puede haber procesos de maxima prioridad que no se ejecuten nunca.