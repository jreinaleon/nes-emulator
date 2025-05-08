#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <stdint.h>
#include <SDL2/SDL.h>

#define SCREEN_WIDTH 256
#define SCREEN_HEIGHT 240

extern SDL_Window* window;
extern SDL_Renderer* renderer;
extern SDL_Texture* texture;
extern uint32_t framebuffer[SCREEN_WIDTH * SCREEN_HEIGHT];

void init_graphics();
void render_frame();
void destroy_graphics();

#endif
