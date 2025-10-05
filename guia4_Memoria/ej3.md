## a) Instalar una CPU mas rapida
No tendrá un gran impacto en el rendimiento del sistema. Al hacer trashing, el cuello de botella se produce por el constante swapping de páginas.  
El uso del CPU es bajo, no se aprovecharía la mejora de velocidad.

## b) Instalar un disco de paginado mas grande.
El problema es la cantidad de espacio en memoria, no en disco. Por mas que aumenten la cantidad de paginas en disco, si hay trashing, el rendimiento seguirá siendo el mismo.

## c) Incrementar el grado de multiprogramacion
Será contraproducente. Al aumentar la cantidad de procesos en memoria, se aumenta la necesidad de swapear paginas, lo que aumenta el trashing.

## d) Disminuir el grado de multiprogramacion
Mejorará el rendimiento. Al haber menos procesos en memoria, habrá menos necesidad de swapear paginas, lo que reduce el trashing y permite que la CPU se utilice en tareas productivas y no en mantenimiento.

## e) Instalar mas memoria principal
Mejorará el rendimiento. Aumentan la cantidad de paginas que pueden estar en memoria, lo que reduce la necesidad de swapear paginas y el trashing.

## f) Instalar un disco mas rapido
Mejorará el rendimiento. Al reducirse el tiempo de acceso al disco, se reduce el tiempo que la CPU está inactiva esperando a que se completen las operaciones de swap.

## g) Incrementar el tamaño de las paginas
Depende... Favoreceria el principio de localidad, pero tambien entrarian menos paginas en memoria, lo que aumentaria el trashing.

## h) Incrementar la velociadad del bus de E/S
Solo se está utilizando el 10% de E/S, por lo que no tendría un gran impacto en el rendimiento del sistema.