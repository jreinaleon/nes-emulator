#ifndef PPU_H
#define PPU_H

#include <SDL2/SDL.h>
#include <stdint.h>

// Definición de la resolución de la pantalla de la NES
#define PPU_WIDTH      256
#define PPU_HEIGHT     240
#define PPU_FRAME_SIZE (PPU_WIDTH * PPU_HEIGHT)

// Paletas de colores de la NES
#define PALETTE_SIZE   64
extern uint32_t NES_PALETTE[PALETTE_SIZE];

// Estructura de la PPU
typedef struct {
    SDL_Renderer* renderer;
    SDL_Texture* texture;
    uint8_t* vram;    // Video RAM
    uint8_t* oam;     // Object Attribute Memory (para los sprites)
    uint16_t pc;      // Contador de ciclo de la PPU
} ppu_t;

extern ppu_t ppu; // PPU global variable

// Funciones principales de la PPU
int ppu_init(ppu_t* ppu, SDL_Window* window);
void ppu_reset(ppu_t* ppu);
void ppu_update(ppu_t* ppu);
void ppu_render(ppu_t* ppu);
void ppu_cleanup(ppu_t* ppu);

#endif // PPU_H
