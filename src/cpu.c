// cpu.c
#include "cpu.h"
#include "memory.h"
#include "apu.h"
#include "ppu.h"
#include "cpu_instructions.h"

// Definición de la estructura CPU
cpu_t cpu;

// Función de inicialización de la CPU
void cpu_init(cpu_t* cpu) {
    cpu->a = 0;      // Registro acumulador
    cpu->x = 0;      // Registro X
    cpu->y = 0;      // Registro Y
    cpu->sp = 0xFD;  // Puntero de pila
    cpu->pc = 0xC000; // Dirección de inicio del programa (puede variar)
    cpu->status = 0x34; // Estado inicial (por ejemplo, interrupciones deshabilitadas)
    cpu->cycles = 0;
}

// Función de ciclo de la CPU
void cpu_step(cpu_t* cpu, memory_t* mem) {
    uint8_t opcode = read_byte(cpu->pc); // Leer el próximo byte (opcode)
    cpu->pc++; // Incrementar el contador de programa

    // Ejecutar la instrucción correspondiente
    execute_instruction(cpu, mem);

    //cpu->cycles += instruction_cycles(opcode); // Sumar los ciclos de la instrucción
}

// Función que establece los flags Z y N
void set_zn_flags(cpu_t* cpu, uint8_t value) {
    cpu->status &= ~(STATUS_Z | STATUS_N); // Limpiar los flags Z y N
    if (value == 0) {
        cpu->status |= STATUS_Z; // Establecer el flag Z si el valor es cero
    }
    if (value & 0x80) {
        cpu->status |= STATUS_N; // Establecer el flag N si el bit más significativo está activado
    }
}

// Función para leer un byte de la memoria
uint8_t read_byte(uint16_t address) {
    return memory.data[address]; // Asumiendo que 'memory' es un arreglo de memoria global
}

// Función para escribir un byte en la memoria
void write_byte(uint16_t address, uint8_t value) {
    memory.data[address] = value; // Asumiendo que 'memory' es un arreglo de memoria global
}

// Función que maneja las interrupciones de la CPU
void handle_interrupts() {
    if (cpu.status & STATUS_IRQ) {
        // Si hay una interrupción, se maneja aquí (esto es solo un ejemplo)
        cpu.status &= ~STATUS_IRQ; // Deshabilitar la interrupción
        // Lógica de manejo de interrupción (por ejemplo, cambiar el PC)
    }
}

// Función que simula un reset de la CPU
void cpu_reset(cpu_t* cpu, memory_t* mem) {
    cpu_init(cpu); // Re-inicializar la CPU
    // Opcional: realizar alguna otra configuración de hardware si es necesario
}


