#include "rom.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static bool is_valid_ines_header(uint8_t *header) {
    return header[0] == 'N' && header[1] == 'E' && header[2] == 'S' && header[3] == 0x1A;
}

Rom *load_rom(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        perror("Error abriendo la ROM");
        return NULL;
    }

    Rom *rom = (Rom *)calloc(1, sizeof(Rom));
    if (!rom) {
        fclose(file);
        return NULL;
    }

    fread(rom->header, 1, INES_HEADER_SIZE, file);
    if (!is_valid_ines_header(rom->header)) {
        fprintf(stderr, "ROM inválida: cabecera iNES no válida\n");
        free(rom);
        fclose(file);
        return NULL;
    }

    rom->prg_rom_banks = rom->header[4];
    rom->chr_rom_banks = rom->header[5];

    uint8_t flags6 = rom->header[6];
    uint8_t flags7 = rom->header[7];

    rom->mapper = (flags7 & 0xF0) | (flags6 >> 4);
    rom->has_trainer = (flags6 & 0x04) != 0;
    rom->vertical_mirroring = (flags6 & 0x01) != 0;
    rom->battery_backed = (flags6 & 0x02) != 0;
    rom->four_screen = (flags6 & 0x08) != 0;

    if (rom->has_trainer) {
        rom->trainer = (uint8_t *)malloc(TRAINER_SIZE);
        fread(rom->trainer, 1, TRAINER_SIZE, file);
    }

    size_t prg_size = rom->prg_rom_banks * 16384;
    rom->prg_rom = (uint8_t *)malloc(prg_size);
    fread(rom->prg_rom, 1, prg_size, file);

    size_t chr_size = rom->chr_rom_banks * 8192;
    if (chr_size > 0) {
        rom->chr_rom = (uint8_t *)malloc(chr_size);
        fread(rom->chr_rom, 1, chr_size, file);
    }

    fclose(file);
    return rom;
}

void free_rom(Rom *rom) {
    if (!rom) return;
    free(rom->trainer);
    free(rom->prg_rom);
    free(rom->chr_rom);
    free(rom);
}
