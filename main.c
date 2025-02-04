#include <SDL2/SDL.h>
#include <time.h>
#include "breslinesub.h"
#include "render.h"

int main(void) {
    GraphicsContext* ctx = createGraphicsContext(1024, 768);
    if (!ctx) return 1;
    
    srand(time(NULL));
    int frameCount = 0;
    int lineCount = 0;
    Uint32 lastTime = SDL_GetTicks();
    Uint32 lastFPSTime = lastTime;
    
    SDL_Event event;
    int running = 1;
    
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            } else if (event.type == SDL_WINDOWEVENT) {
                if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
                    handleGraphicsResize(ctx, event.window.data1, event.window.data2);
                }
            }
        }
        
        clearGraphicsContext(ctx);
        
        for (int i = 0; i < 100; i++) {
            int x0 = rand() % ctx->width;
            int y0 = rand() % ctx->height;
            int x1 = rand() % ctx->width;
            int y1 = rand() % ctx->height;
            uint8_t r = rand() % 256;
            uint8_t g = rand() % 256;
            uint8_t b = rand() % 256;
            
            drawAALine(x0, y0, x1, y1, r, g, b, putPixelGraphicsContext, ctx);
            lineCount++;
        }
        
        updateGraphicsContext(ctx);
        frameCount++;
        
        Uint32 currentTime = SDL_GetTicks();
        if (currentTime - lastFPSTime >= 1000) {
            float fps = frameCount * 1000.0f / (currentTime - lastFPSTime);
            float lps = lineCount * 1000.0f / (currentTime - lastFPSTime);
            printf("FPS: %.2f, Lines/sec: %.2f\n", fps, lps);
            
            frameCount = 0;
            lineCount = 0;
            lastFPSTime = currentTime;
        }
    }
    
    destroyGraphicsContext(ctx);
    return 0;
}
