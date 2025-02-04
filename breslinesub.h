#ifndef BRESLINESUB_H
#define BRESLINESUB_H

#include <stdint.h>

typedef void (*PutPixelCallback)(int x, int y, uint8_t r, uint8_t g, uint8_t b, uint8_t a, void* userData);

void drawAALine(int x0, int y0, int x1, int y1, 
                uint8_t r, uint8_t g, uint8_t b,
                PutPixelCallback callback, void* userData);

#endif
