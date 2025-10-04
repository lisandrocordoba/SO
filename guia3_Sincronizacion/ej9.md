Necesitamos un semaforo barrera inicializado en 0, un contador y otro semaforo mutex para aislar el contador.

Cada proceso aumentará el contador al finalizar las sentencias Ai y luego barrera.wait() esperando a que los demas procesos hagan sus respectivos Ai.

Antes del wait, se chequea si contador == n, el ultimo proceso en terminar sus Ai entrara al if y hará N barrera.signal() para despertar a todos los procesos (*) que estan esperando en barrera (incluyendose).

Luego del barrera.wait(), cada proceso ejecuta sus Bi.

(*) Otra opcion en cambio de los N signal, es hacer 1 solo y que cada uno luego de despertarte del wait haga otro signal (molinete).