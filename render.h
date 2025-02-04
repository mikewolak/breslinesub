#ifndef RENDER_H
#define RENDER_H

#include <SDL2/SDL.h>

typedef struct {
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* texture;
    uint32_t* pixels;
    int width;
    int height;
} GraphicsContext;

GraphicsContext* createGraphicsContext(int width, int height);
void destroyGraphicsContext(GraphicsContext* ctx);
void clearGraphicsContext(GraphicsContext* ctx);
void updateGraphicsContext(GraphicsContext* ctx);
void handleGraphicsResize(GraphicsContext* ctx, int width, int height);
void putPixelGraphicsContext(int x, int y, uint8_t r, uint8_t g, uint8_t b, uint8_t a, void* userData);

#endif
