#ifndef CPU_H
#define CPU_H

#include <stdint.h>
#include <stddef.h>
#include "memory.h"

// Definición de las banderas de la CPU
#define FLAG_CARRY      0x01
#define FLAG_ZERO       0x02
#define FLAG_INTERRUPT  0x04
#define FLAG_DECIMAL    0x08
#define FLAG_BREAK      0x10
#define FLAG_UNUSED     0x20
#define FLAG_OVERFLOW   0x40
#define FLAG_NEGATIVE   0x80

#define STATUS_Z (1 << 1)  // Zero flag
#define STATUS_N (1 << 7)  // Negative flag
#define STATUS_IRQ (1 << 2)  // IRQ disable flag

#define MEM_SIZE        0x10000  // 64 KB de memoria

// Estructura de la CPU
typedef struct {
    uint8_t a;    // Acumulador
    uint8_t x;    // Registro X
    uint8_t y;    // Registro Y
    uint8_t sp;   // Puntero de pila
    uint8_t p;    // Registro de banderas
    uint16_t pc;  // Contador de programa
    uint8_t status; // Estado inicial (por ejemplo, interrupciones deshabilitadas)
    uint32_t cycles;
} cpu_t;

extern cpu_t cpu;        // CPU global
extern memory_t memory;  // Memoria global

// Funciones principales de la CPU
void cpu_init(cpu_t* cpu);
void cpu_reset(cpu_t* cpu, memory_t* mem);
void cpu_load_program(cpu_t* cpu, memory_t* mem, uint8_t* program, size_t size, uint16_t start_addr);
void cpu_step(cpu_t* cpu, memory_t* mem);
void cpu_run(cpu_t* cpu, memory_t* mem);
void execute_instruction(cpu_t* cpu, memory_t* mem);
void set_zn_flags(cpu_t* cpu, uint8_t value);
void cpu_debug_dump(const cpu_t* cpu);

// Declaraciones de funciones
uint8_t read_byte(uint16_t address);
uint8_t instruction_cycles(uint8_t opcode);

// Funciones de acceso a memoria (útiles para debugging o extensión)
uint8_t cpu_read(memory_t* mem, uint16_t addr);
void cpu_write(memory_t* mem, uint16_t addr, uint8_t value);

#endif // CPU_H


