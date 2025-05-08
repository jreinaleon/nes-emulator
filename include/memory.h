#ifndef MEMORY_H
#define MEMORY_H

#include <stdint.h>

// Memoria completa de la NES (64 KB)
typedef struct {
    uint8_t data[0x10000];
} memory_t;

extern memory_t memory;

void init_memory(memory_t* memory);

// Lectura de memoria
uint8_t mem_read(memory_t* mem, uint16_t addr);

// Escritura en memoria
void mem_write(memory_t* mem, uint16_t addr, uint8_t value);

#endif // MEMORY_H
