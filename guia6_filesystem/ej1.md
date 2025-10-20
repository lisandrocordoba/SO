No contamos con memoria cache y la FAT no queda almacenada en memoria.
Suponiendo que sabemos el primer bloque del archivo, debemos:
- Traer del disco ese bloque
- Traer del disco la FAT
- Buscar cual es el siguiente bloque
- Repetir

Es decir, por cada bloque necesitamos 2 accesos al disco.  
Para llegar hasta el bloque N necesitaremos 2 * N accesos.