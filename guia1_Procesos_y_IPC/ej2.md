*2a)*

```c
 struct PCB {
    int STAT;       // valores posibles KE_RUNNING, KE_READY, KE_BLOCKED, KE_NEW
    int P_ID;       // process ID
    int PC;         // valor del PC del proceso al ser desalojado
    int RO;         // valor del registro R0 al ser desalojado
    ...
    int R15;        // valor del registro R15 al ser desalojado
    int CPU_TIME    // tiempo de ejecución del proceso
 }c

void Ke_context_switch(PCB* pcb_0, PCB* pcb_1){

    // DESALOJAR PROCESO 0
    pcb_0->STAT .=. KE_READY;             // pasa a estado READY 
    pcb_0->PC .=. PC;                     // guarda el valor del PC
    pcb_0->RO .=. R0;                     // guarda el valor del registro R0
    ...                                   // guarda el valor de los demás registros
    pcb_0->R15 .=. R15;                   // guarda el valor del registro R15
    pcb_0->CPU_TIME += ke_current_user_time();  // incrementar el tiempo de CPU del proceso

    // ALOJAR PROCESO 1
    pcb_1->STAT = KE_RUNNING;           // pasa a estado RUNNING
    PC .=. pcb_1->PC;                   // restaura el valor del PC
    R0 .=. pcb_1->R0;                   // restaura el valor del registro R0
    ...                                 // restaura el valor de los demás registros
    R15 .=. pcb_1->R15;                 // restaura el valor del registro R15

    ke_reset_current_user_time();       // reinicia el contador de tiempo de CPU
    set_current_process(pcb_1->P_ID);   // actualiza el proceso actual
    
    ret()
}
```