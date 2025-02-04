#include "breslinesub.h"
#include <stdlib.h>
#include <math.h>

static inline float fpart(float x) {
    return x - floorf(x);
}

static inline float rfpart(float x) {
    return 1.0f - fpart(x);
}

void drawAALine(int x0, int y0, int x1, int y1,
                uint8_t r, uint8_t g, uint8_t b,
                PutPixelCallback callback, void* userData) {
    // Implementation remains the same
    float dx = (float)(x1 - x0);
    float dy = (float)(y1 - y0);
    float gradient;
    float xend, yend, xgap, intersectY;
    float step;
    int x, ix1, ix2;
    
    if (fabsf(dx) > fabsf(dy)) {
        if (x1 < x0) {
            int tx = x0; x0 = x1; x1 = tx;
            int ty = y0; y0 = y1; y1 = ty;
            dx = -dx;
            dy = -dy;
        }
        
        gradient = dy / dx;
        xend = roundf(x0);
        yend = y0 + gradient * (xend - x0);
        xgap = rfpart(x0 + 0.5f);
        ix1 = (int)xend;
        intersectY = yend;
        
        callback(ix1, (int)intersectY, r, g, b, 
                (uint8_t)(rfpart(yend) * xgap * 255), userData);
        callback(ix1, (int)intersectY + 1, r, g, b,
                (uint8_t)(fpart(yend) * xgap * 255), userData);
        
        xend = roundf(x1);
        yend = y1 + gradient * (xend - x1);
        xgap = fpart(x1 + 0.5f);
        ix2 = (int)xend;
        step = gradient;
        
        for (x = ix1 + 1; x < ix2; x++) {
            callback(x, (int)intersectY, r, g, b,
                    (uint8_t)(rfpart(intersectY) * 255), userData);
            callback(x, (int)intersectY + 1, r, g, b,
                    (uint8_t)(fpart(intersectY) * 255), userData);
            intersectY += step;
        }
    } else {
        // Vertical line case remains the same
        if (y1 < y0) {
            int tx = x0; x0 = x1; x1 = tx;
            int ty = y0; y0 = y1; y1 = ty;
            dx = -dx;
            dy = -dy;
        }
        
        gradient = dx / dy;
        float temp = x0;
        x0 = y0;
        y0 = temp;
        temp = x1;
        x1 = y1;
        y1 = temp;
        dx = y1 - y0;
        dy = x1 - x0;
        
        xend = roundf(x0);
        yend = y0 + gradient * (xend - x0);
        xgap = rfpart(x0 + 0.5f);
        ix1 = (int)xend;
        intersectY = yend;
        
        callback((int)intersectY, ix1, r, g, b,
                (uint8_t)(rfpart(yend) * xgap * 255), userData);
        callback((int)intersectY + 1, ix1, r, g, b,
                (uint8_t)(fpart(yend) * xgap * 255), userData);
        
        xend = roundf(x1);
        yend = y1 + gradient * (xend - x1);
        xgap = fpart(x1 + 0.5f);
        ix2 = (int)xend;
        step = gradient;
        
        for (x = ix1 + 1; x < ix2; x++) {
            callback((int)intersectY, x, r, g, b,
                    (uint8_t)(rfpart(intersectY) * 255), userData);
            callback((int)intersectY + 1, x, r, g, b,
                    (uint8_t)(fpart(intersectY) * 255), userData);
            intersectY += step;
        }
    }
}

