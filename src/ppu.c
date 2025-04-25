#include "ppu.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

ppu_t ppu;

// Implementación de la paleta de la NES
uint32_t NES_PALETTE[PALETTE_SIZE] = {
    0x000000, 0x555555, 0xAA5555, 0xFF5555, 0x55AA55, 0xAAAA55, 0xFFAA55, 0xFFFFFF,
    0x5555AA, 0xAAAAAA, 0xFFAAAA, 0x5555FF, 0xAAAAFF, 0xFFAAFF, 0x5555FF, 0x5555FF,
    0x1A1A1A, 0x2A2A2A, 0x3A3A3A, 0x4A4A4A, 0x5A5A5A, 0x6A6A6A, 0x7A7A7A, 0x8A8A8A,
    0x9A9A9A, 0xAAAAAA, 0xBAAAAA, 0xCAAAAA, 0xDAAAAA, 0xEAAAAA, 0xFAAAAA, 0xFFFFFF,
    0x1A3A3A, 0x1A4A4A, 0x1A5A5A, 0x1A6A6A, 0x1A7A7A, 0x1A8A8A, 0x1A9A9A, 0x1AAAAA,
    0x1ABBBB, 0x1ACCCC, 0x1ADDDE, 0x1AEEEE, 0x1BFFFF, 0x1C1111, 0x1D1212, 0x1E1313
};

// Inicializa la PPU y configura SDL
int ppu_init(ppu_t* ppu, SDL_Window* window) {
    ppu->renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!ppu->renderer) {
        printf("Error al crear el renderizador: %s\n", SDL_GetError());
        return -1;
    }

    ppu->texture = SDL_CreateTexture(ppu->renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, PPU_WIDTH, PPU_HEIGHT);
    if (!ppu->texture) {
        printf("Error al crear la textura: %s\n", SDL_GetError());
        return -1;
    }

    ppu->vram = (uint8_t*)malloc(0x4000);  // VRAM de la NES (16KB)
    if (!ppu->vram) {
        printf("Error al asignar memoria para VRAM\n");
        return -1;
    }

    ppu->oam = (uint8_t*)malloc(0x100);    // OAM (256 bytes)
    if (!ppu->oam) {
        printf("Error al asignar memoria para OAM\n");
        return -1;
    }

    ppu->pc = 0;

    return 0;
}

// Reinicia la PPU a su estado inicial
void ppu_reset(ppu_t* ppu) {
    memset(ppu->vram, 0, 0x4000);  // Limpiar VRAM
    memset(ppu->oam, 0, 0x100);    // Limpiar OAM
    ppu->pc = 0;
}

// Actualiza la PPU, puede ser llamada en cada ciclo
void ppu_update(ppu_t* ppu) {
    // Lógica de actualización de la PPU aquí, como las interrupciones y ciclos.
    // Para fines de simplificación, este ejemplo no implementa todas las características.
    ppu->pc++;

    if (ppu->pc >= 341) {
        ppu->pc = 0;
    }
}

// Renderiza la imagen generada por la PPU usando SDL
void ppu_render(ppu_t* ppu) {
    uint32_t pixels[PPU_FRAME_SIZE];

    // Lógica de renderizado de la imagen, aquí solo pintamos con un color
    // Simplemente una pantalla llena de color negro por ahora (esto es solo un ejemplo).
    for (int i = 0; i < PPU_FRAME_SIZE; i++) {
        pixels[i] = NES_PALETTE[0];  // Usamos la primera paleta (negra)
    }

    // Actualiza la textura con los píxeles generados
    SDL_UpdateTexture(ppu->texture, NULL, pixels, PPU_WIDTH * sizeof(uint32_t));

    // Limpia el renderizador y dibuja la textura en la ventana
    SDL_RenderClear(ppu->renderer);
    SDL_RenderCopy(ppu->renderer, ppu->texture, NULL, NULL);
    SDL_RenderPresent(ppu->renderer);
}

// Limpia y libera los recursos de la PPU
void ppu_cleanup(ppu_t* ppu) {
    if (ppu->vram) {
        free(ppu->vram);
    }

    if (ppu->oam) {
        free(ppu->oam);
    }

    if (ppu->texture) {
        SDL_DestroyTexture(ppu->texture);
    }

    if (ppu->renderer) {
        SDL_DestroyRenderer(ppu->renderer);
    }
}
