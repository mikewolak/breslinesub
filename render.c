#include "render.h"
#include <stdlib.h>
#include <string.h>

GraphicsContext* createGraphicsContext(int width, int height) {
    GraphicsContext* ctx = calloc(1, sizeof(GraphicsContext));
    if (!ctx) return NULL;
    
    ctx->width = width;
    ctx->height = height;
    
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        free(ctx);
        return NULL;
    }
    
    ctx->window = SDL_CreateWindow("Line Test",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        width, height,
        SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if (!ctx->window) goto cleanup;
    
    ctx->renderer = SDL_CreateRenderer(ctx->window, -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!ctx->renderer) goto cleanup;
    
    ctx->texture = SDL_CreateTexture(ctx->renderer,
        SDL_PIXELFORMAT_ARGB8888,
        SDL_TEXTUREACCESS_STREAMING,
        width, height);
    if (!ctx->texture) goto cleanup;
    
    ctx->pixels = calloc(width * height, sizeof(uint32_t));
    if (!ctx->pixels) goto cleanup;
    
    return ctx;

cleanup:
    destroyGraphicsContext(ctx);
    return NULL;
}

void destroyGraphicsContext(GraphicsContext* ctx) {
    if (!ctx) return;
    
    free(ctx->pixels);
    SDL_DestroyTexture(ctx->texture);
    SDL_DestroyRenderer(ctx->renderer);
    SDL_DestroyWindow(ctx->window);
    SDL_Quit();
    free(ctx);
}

void clearGraphicsContext(GraphicsContext* ctx) {
    memset(ctx->pixels, 0, ctx->width * ctx->height * sizeof(uint32_t));
}

void updateGraphicsContext(GraphicsContext* ctx) {
    SDL_UpdateTexture(ctx->texture, NULL, ctx->pixels, ctx->width * sizeof(uint32_t));
    SDL_RenderCopy(ctx->renderer, ctx->texture, NULL, NULL);
    SDL_RenderPresent(ctx->renderer);
}

void handleGraphicsResize(GraphicsContext* ctx, int width, int height) {
    ctx->width = width;
    ctx->height = height;
    
    free(ctx->pixels);
    ctx->pixels = calloc(width * height, sizeof(uint32_t));
    
    SDL_DestroyTexture(ctx->texture);
    ctx->texture = SDL_CreateTexture(ctx->renderer,
        SDL_PIXELFORMAT_ARGB8888,
        SDL_TEXTUREACCESS_STREAMING,
        width, height);
}

void putPixelGraphicsContext(int x, int y, uint8_t r, uint8_t g, uint8_t b, uint8_t a, void* userData) {
    GraphicsContext* ctx = (GraphicsContext*)userData;
    if (!ctx || x < 0 || x >= ctx->width || y < 0 || y >= ctx->height) return;
    
    uint32_t color = (a << 24) | (r << 16) | (g << 8) | b;
    ctx->pixels[y * ctx->width + x] = color;
}

