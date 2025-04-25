#ifndef ROM_H
#define ROM_H

#include <stdint.h>
#include <stdbool.h>

#define INES_HEADER_SIZE 16
#define TRAINER_SIZE 512

typedef struct {
    uint8_t header[INES_HEADER_SIZE];
    uint8_t prg_rom_banks;
    uint8_t chr_rom_banks;
    uint8_t mapper;
    bool has_trainer;
    bool vertical_mirroring;
    bool battery_backed;
    bool four_screen;
    uint8_t *trainer;
    uint8_t *prg_rom;
    uint8_t *chr_rom;
} Rom;

Rom *load_rom(const char *filename);
void free_rom(Rom *rom);

#endif // ROM_H
