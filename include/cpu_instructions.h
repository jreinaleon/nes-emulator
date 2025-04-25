// cpu_instructions.h
#ifndef CPU_INSTRUCTIONS_H
#define CPU_INSTRUCTIONS_H

#include <stdint.h>

// Prototipos de las funciones de las instrucciones
void execute_instruction(cpu_t* cpu, memory_t* mem);
void reset_cpu(cpu_t* cpu);


// Otros prototipos de instrucciones según lo necesites

#endif // CPU_INSTRUCTIONS_H