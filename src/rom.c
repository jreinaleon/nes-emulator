#include "rom.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Función auxiliar para validar la firma de la cabecera iNES.
static bool is_valid_ines_header(uint8_t *header) {
    // La cabecera iNES debe iniciar con 'N', 'E', 'S' y 0x1A
    return header[0] == 'N' &&
           header[1] == 'E' &&
           header[2] == 'S' &&
           header[3] == 0x1A;
}

Rom *load_rom(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        perror("Error abriendo la ROM");
        return NULL;
    }

    // Reservar memoria para la estructura Rom
    Rom *rom = (Rom *)calloc(1, sizeof(Rom));
    if (!rom) {
        fclose(file);
        return NULL;
    }

    // Leer los 16 bytes de cabecera
    if (fread(rom->header, 1, INES_HEADER_SIZE, file) != INES_HEADER_SIZE) {
        fprintf(stderr, "Error al leer la cabecera iNES\n");
        free(rom);
        fclose(file);
        return NULL;
    }

    // Validar la cabecera iNES
    if (!is_valid_ines_header(rom->header)) {
        fprintf(stderr, "ROM inválida: cabecera iNES no válida\n");
        free(rom);
        fclose(file);
        return NULL;
    }

    // Interpretar la cabecera:
    rom->prg_rom_banks = rom->header[4];   // Tamaño de PRG-ROM (en bloques de 16 KB)
    rom->chr_rom_banks = rom->header[5];     // Tamaño de CHR-ROM (en bloques de 8 KB)

    uint8_t flags6 = rom->header[6];
    uint8_t flags7 = rom->header[7];

    // Calcula el mapper:
    // El mapper se obtiene combinando el nibble alto de flags7 con el nibble alto de flags6.
    rom->mapper = ((flags7 & 0xF0)) | (flags6 >> 4);

    // Flags de características:
    rom->has_trainer = (flags6 & 0x04) != 0;
    rom->vertical_mirroring = (flags6 & 0x01) != 0;
    rom->battery_backed = (flags6 & 0x02) != 0;
    rom->four_screen = (flags6 & 0x08) != 0;

    // Si existe un "trainer", se lee su contenido (512 bytes) y se guarda
    if (rom->has_trainer) {
        rom->trainer = (uint8_t *)malloc(TRAINER_SIZE);
        if (fread(rom->trainer, 1, TRAINER_SIZE, file) != TRAINER_SIZE) {
            fprintf(stderr, "Error al leer el trainer\n");
            free_rom(rom);
            fclose(file);
            return NULL;
        }
    }

    // Leer PRG-ROM: Cada banco es de 16 KB
    size_t prg_size = rom->prg_rom_banks * 16384;
    rom->prg_rom = (uint8_t *)malloc(prg_size);
    if (!rom->prg_rom || fread(rom->prg_rom, 1, prg_size, file) != prg_size) {
        fprintf(stderr, "Error al leer la PRG-ROM\n");
        free_rom(rom);
        fclose(file);
        return NULL;
    }

    // Leer CHR-ROM: Cada banco es de 8 KB (si existe; 0 indica que se usará RAM en su lugar)
    size_t chr_size = rom->chr_rom_banks * 8192;
    if (chr_size > 0) {
        rom->chr_rom = (uint8_t *)malloc(chr_size);
        if (!rom->chr_rom || fread(rom->chr_rom, 1, chr_size, file) != chr_size) {
            fprintf(stderr, "Error al leer la CHR-ROM\n");
            free_rom(rom);
            fclose(file);
            return NULL;
        }
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
