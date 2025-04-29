#ifndef ROM_H
#define ROM_H

#include <stdint.h>
#include <stdbool.h>

#define INES_HEADER_SIZE 16
#define TRAINER_SIZE 512

typedef struct {
    uint8_t header[INES_HEADER_SIZE];  // Cabecera completa iNES
    uint8_t prg_rom_banks;             // Bancos de PRG (16 KB cada uno)
    uint8_t chr_rom_banks;             // Bancos de CHR (8 KB cada uno)
    uint8_t mapper;                    // Mapper calculado a partir de los flags
    bool has_trainer;                  // Indica si existe sección trainer
    bool vertical_mirroring;           // Mirroring: vertical u horizontal
    bool battery_backed;               // Indica si hay RAM respaldada
    bool four_screen;                  // Indica configuración de 4 pantallas
    uint8_t *trainer;                  // Datos del trainer (si existe)
    uint8_t *prg_rom;                  // Datos de la PRG-ROM
    uint8_t *chr_rom;                  // Datos de la CHR-ROM
} Rom;

Rom *load_rom(const char *filename);
void free_rom(Rom *rom);

#endif // ROM_H
