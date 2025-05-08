#ifndef EMULATOR_H
#define EMULATOR_H

#include <SDL2/SDL.h>

typedef struct {
    const char *rom_path;
    SDL_Window *window;
} emulation_params_t;

void init_emulation(emulation_params_t params);
void shutdown_emulation();

#endif