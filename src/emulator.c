#include <stdio.h>
#include <stdlib.h>
#include "emulator.h"
#include "memory.h"
#include "cpu.h"
#include "ppu.h"
#include "apu.h"
#include "rom.h"

Rom *loaded_rom = NULL;

void map_prg_rom(Rom *rom) {
    if (rom->prg_rom_banks == 1) {
        memcpy(&memory.data[0x8000], rom->prg_rom, 0x4000);
        memcpy(&memory.data[0xC000], rom->prg_rom, 0x4000);
    } else if (rom->prg_rom_banks == 2) {
        memcpy(&memory.data[0x8000], rom->prg_rom, 0x8000);
    } else {
        fprintf(stderr, "Número de bancos PRG no soportado: %d\n", rom->prg_rom_banks);
        exit(1);
    }
}

void init_emulation(emulation_params_t params) { // Use the struct
    loaded_rom = load_rom(params.rom_path);
    if (!loaded_rom) {
        fprintf(stderr, "Error cargando la ROM.\n");
        exit(1);
    }

    init_memory(&memory);
    map_prg_rom(loaded_rom);
    cpu_init(&cpu);
    ppu_init(&ppu, params.window); // Pass the window
    init_apu(&apu);
}

void shutdown_emulation() {
    free_rom(loaded_rom);
}