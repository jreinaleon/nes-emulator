#include "memory.h"
#include <string.h>

memory_t memory;

void init_memory(memory_t* memory) {
    // Inicializa la memoria a 0
    memset(memory->data, 0, 0x10000);
}

// Función de lectura de memoria
uint8_t mem_read(memory_t* mem, uint16_t addr) {
    // Aquí podrías agregar lógica para manejar direcciones especiales (por ejemplo, puertos I/O)
    // Si no, simplemente devuelves el valor de la memoria en la dirección especificada.
    return mem->data[addr];
}

// Función de escritura de memoria
void mem_write(memory_t* mem, uint16_t addr, uint8_t value) {
    // Aquí también podrías manejar direcciones especiales.
    // Si no, simplemente asignas el valor a la memoria en la dirección especificada.
    mem->data[addr] = value;
}
