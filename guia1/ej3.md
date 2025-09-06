**syscall**: llamada a un servicio proveido por el SO, se ejecuta en modo Kernel ya que no es el proceso quien la ejecuta, sino SO.

**llamada a funcion de libreria**: el proceso busca codigo de la funcion guardada en la libreria y es él mismo quien lo ejecuta, manteniendo el modo Usuario. Es como un "copy & paste" de la funcion encapsulada.
(Notar que la funcion puede tener una syscall adentro y ahi si vale lo explicado antes)