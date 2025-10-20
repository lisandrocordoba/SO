- Disk size: 128 GB
- Block size: 8 KB
- FAT entry size: 24 B

### a) Tamaño de la tabla FAT
1 KB = 2^10  y 8 = 2^3 --> 8 KB = 2^13  
1 MB = 2^20  
1 GB = 2^30  y 128 = 2^7 --> 128 GB = 2^37  
 

Hay 128 GB / 8 KB = 2^24 bloques.  
La FAT tiene una entry por bloque, por lo que su tamaño será 2^24 * 24 = 2^20 * 2^4 * 24 = 1 MB * 384 = 384 MB

### b) Cuanto archivos de 10 MB es posible almacenar?
128 GB / 10 MB = 