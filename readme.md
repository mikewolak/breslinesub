# Subpixel Anti-aliased Line Drawing Library

A high-performance C99 library implementing Bresenham's line algorithm with subpixel anti-aliasing.

## Technical Details

### Subpixel Anti-aliasing Implementation

The library implements subpixel precision using intensity modulation. For each pixel near the ideal line:

1. **Endpoint Calculation**
   - Uses `fpart()` and `rfpart()` to get fractional parts of coordinates
   - `fpart(3.7) = 0.7` (fractional part)
   - `rfpart(3.7) = 0.3` (1 - fractional part)

2. **Intensity Distribution**
   For a line passing through (3.7, 2.4):
   ```
   Pixel (3,2):   intensity = rfpart(3.7) * rfpart(2.4) * 255
   Pixel (3,3):   intensity = rfpart(3.7) * fpart(2.4) * 255
   Pixel (4,2):   intensity = fpart(3.7) * rfpart(2.4) * 255
   Pixel (4,3):   intensity = fpart(3.7) * fpart(2.4) * 255
   ```

3. **Alpha Blending**
   - Each affected pixel receives an alpha value based on its distance from the ideal line
   - Creates smooth appearance by distributing intensity across adjacent pixels
   - Alpha values sum to 255 for consistent line intensity

4. **Steep vs. Shallow Lines**
   - Algorithm detects line slope: |dx| > |dy|
   - Shallow lines: iterate along x-axis
   - Steep lines: iterate along y-axis with coordinate swap
   - Ensures consistent pixel density regardless of angle

### Architecture

1. **Graphics System Independence**
   - Uses callback function for pixel plotting
   - Graphics context passed as void* userData
   - Allows easy integration with any rendering backend

2. **SDL2 Reference Implementation**
   - Resizable window support
   - Double-buffered rendering
   - VSYNC support
   - 32-bit ARGB color format

3. **Performance Features**
   - Optimized endpoint calculations
   - Single-pass rendering
   - Minimal branching in inner loops
   - Pre-calculated gradients
   - FPS and lines/second monitoring

## Build Requirements

- C99 compliant compiler
- SDL2 development libraries
- pkg-config
- make

## Building

```bash
make
```

## Usage

```c
// Create graphics context
GraphicsContext* ctx = createGraphicsContext(1024, 768);

// Draw a line
drawAALine(x0, y0, x1, y1, r, g, b, putPixelCallback, userData);

// Clean up
destroyGraphicsContext(ctx);
```

## Performance

The demo renders 100 random lines per frame at 60 FPS, with typical performance of:
- 6000 anti-aliased lines per second
- Full window resize capability
- Consistent frame timing with VSYNC

## License

Released under MIT License