# Ejercico 3
Tenemo un filesystem parecido a ext2:
- Bloques de 4 KB
- Direccionamiento a bloques de disco (LBA) de 8 B
- Entradas del inodo:
    - 5 directas
    - 2 indirectas
    - 1 doblemente indirecta

### a) Tamaño maximo de archivo que soporta
Separemos en los tipos de entradas:
#### Directa
Direcciona a un bloque de datos de 4 KB
En total hay 5 -> 20 KB
#### Indirecta
Direcciona a un bloque de direcciones logicas a bloques (LBA). Cada LBA es de 8 B y el bloque es de 4 KB, por lo que en un bloque de direcciones entran:  
4 KB / 8 B = 512 LBAs.
Se direccionan 512 bloques de datos, cada uno de 4 KB, por lo que en total una entrada indirecta direcciona:
512 * 4 KB = 2048 KB = 2 MB.  
Hay 2 entradas indirectas, por lo que en total direccionan:
2 * 2 MB = 4 MB.