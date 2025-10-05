### a)
- FIFO desaloja la pagina que fue cargada hace mas tiempo.
- LRU desaloja la pagina que no fue referenciada hace mas tiempo.
- Second Chance desaloja la que fue cargada hace mas tiempo y no fue referenciada.

### b) Algoritmo generico

```
Si la pagina no está en ningun frame:
  Si hay un frame libre:
    Cargar la pagina en el frame libre
    Setear el atributo correspondiente
  Si no hay frames libres:
    Desalojar la pagina segun el atributo correspondiente
    Alojar la nueva pagina en el frame desalojado
    Setear el atributo correspondiente
```