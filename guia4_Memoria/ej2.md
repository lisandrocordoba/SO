16 MB total.

Particiones:
- Particion 1 --> 8 MB
- Particion 2 --> 1 MB
- Particion 3 --> 4 MB
- Particion 4 --> 512 KB
- Particion 5 --> 512 KB
- Particion 6 --> 2 MB

Tamaño de los procesos(en orden de llegada):
- Proceso A --> 500 KB
- Proceso B --> 6 MB
- Proceso C --> 3 MB
- Proceso D --> 20 KB
- Proceso E --> 4 MB


## Best Fit
Disponibles (8 MB, 1 MB, 4 MB, 512 KB, 512 KB, 2 MB).  
#### Proceso A (500 KB)
Se asigna la particion de 512 KB.  
Se genera una particion de 12 KB.
Disponibles (8 MB, 1 MB, 4 MB, 12 KB, 512 KB, 2 MB).  

#### Proceso B (6 MB)
Se asigna la particion de 8 MB.
Se genera una particion de 2 MB.
Disponibles (2 MB, 1 MB, 4 MB, 12 KB, 512 KB, 2 MB).  

#### Proceso C (3 MB)
Se asigna la particion de 4 MB.
Se genera una particion de 1 MB .
Disponibles (2 MB, 1 MB, 1 MB, 12 KB, 512 KB, 2 MB).  

#### Proceso D (20 KB)
Se asigna a la particion de 512 KB.
Se genera una particion de 492 KB.
Disponibles (2 MB, 1 MB, 1 MB, 12 KB, 492 KB, 2 MB).

#### Proceso E (4 MB)
No hay particion disponible.

Cantidad de memoria sin utilizar: 2 MB + 1 MB + 1 MB + 12 KB + 492 KB + 2 MB = 6.504 MB


## First Fit
Disponibles (8 MB, 1 MB, 4 MB, 512 KB, 512 KB, 2 MB).  
#### Proceso A (500 KB)
Se asigna la particion de 8 MB.
Se genera una particion de 7.5 MB.
Disponibles (7.5 MB, 1 MB, 4 MB, 512 KB, 512 KB, 2 MB).

#### Proceso B (6 MB)
Se asigna la particion de 7.5 MB.
Se genera una particion de 1.5 MB.
Disponibles (1.5 MB, 1 MB, 4 MB, 12 KB, 512 KB, 2 MB).  

#### Proceso C (3 MB)
Se asigna la particion de 4 MB.
Se genera una particion de 1 MB.
Disponibles (1.5 MB, 1 MB, 1 MB, 12 KB, 512 KB, 2 MB).  

#### Proceso D (20 KB)
Se asigna a la particion de 1.5 MB.
Se genera una particion de 1.48 MB.
Disponibles (1.48 MB, 1 MB, 1 MB, 12 KB, 512 KB, 2 MB).  

#### Proceso E (4 MB)
No hay particion disponible.

Cantidad de memoria sin utilizar: 1.48 MB + 1 MB + 1 MB + 12 KB + 512 KB + 2 MB = 6.504 MB



## Worst Fit
Disponibles (8 MB, 1 MB, 4 MB, 512 KB, 512 KB, 2 MB).  
#### Proceso A (500 KB)
Se asigna la particion de 8 MB.
Se genera una particion de 7.5 MB.
Disponibles (7.5 MB, 1 MB, 4 MB, 512 KB, 512 KB, 2 MB).

#### Proceso B (6 MB)
Se le asigna a la particion de 7.5 MB.
Se genera una particion de 1.5 MB.
Disponibles (1.5 MB, 1 MB, 4 MB, 512 KB, 512 KB, 2 MB).

#### Proceso C (3 MB)
Se le asigna a la particion de 4 MB.
Se genera una particion de 1 MB.
Disponibles (1.5 MB, 1 MB, 1 MB, 512 KB, 512 KB, 2 MB).

#### Proceso D (20 KB)
Se le asigna a la particion de 2 MB.
Se genera una particion de 1.98 MB.
Disponibles (1.5 MB, 1 MB, 1 MB, 512 KB, 512 KB, 1.98 MB).

#### Proceso E (4 MB)
No hay particion disponible.

Cantidad de memoria sin utilizar: 1.5 MB + 1 MB + 1 MB + 512 KB + 512 KB + 1.98 MB = 6.502 MB

# Conclusión
Los 3 algoritmos tienen aproximadamente la misma cantidad de memoria sin utilizar. Mas aun, la tienen dsitribuida de forma similar, teniendo como maximo 2 MB en una sola particion.  
Ninguno de los algoritmos pudo asignar la particion al proceso E, ya que no habia una particion contigua de 4 MB disponible.