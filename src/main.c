#include <SDL2/SDL.h>
#include "graphics.h"
#include "emulator.h"
#include "cpu.h"
#include "ppu.h"
#include "apu.h"
#include "memory.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Uso: %s archivo_rom.nes\n", argv[0]);
        return 1;
    }

    init_graphics();
    init_emulation(argv[1]);

    int quit = 0;
    SDL_Event event;

    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = 1;
            }
        }

        cpu_step(&cpu, &memory);
        ppu_update(&ppu);
        update_apu(&apu);
        render_frame();

        SDL_Delay(16);
    }

    shutdown_emulation();
    destroy_graphics();
    return 0;
}
