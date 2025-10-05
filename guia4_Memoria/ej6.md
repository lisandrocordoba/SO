## a)
LRU, FIFO y Second Chance no serian efectivos ya que al tener menos frames que paginas usadas y nunca tener referencias cercanas a la misma pagina, en cada paso tendriamos page faults.

## b)
Si tuvieramos 500 frames, un mantener fijos 499 y dejar 1 solo para los pagefault.  
La primera itearación serán todos page faults, pero a partir de la segunda iteración tendremos 499 hits y 513-499=14 page faults.  
El aleatorio puede ser otro page fault, pero estadisticamente la mayoria de las veces será hit
