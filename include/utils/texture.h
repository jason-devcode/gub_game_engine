#ifndef TEXTURE_UTILS_H
#define TEXTURE_UTILS_H

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "image.h"
#include "raster.h"

#include "fast_math/fast_abs.h"

#include "../core/engine_properties/framebuffer.h"
#include "../core/engine_properties/screen_dimensions.h"

typedef struct _tag_texture_
{
    int width;
    int height;
    int totalPixels;
    int totalBytes;
    int bytesPerPixel;
    unsigned int *pixels;
} Texture;

#define fillTextureColor(texture, color)                                \
    unsigned int *pixelIterator = (texture).pixels;                     \
    unsigned int *endPixels = (texture).pixels + (texture).totalPixels; \
    for (; pixelIterator < endPixels; ++pixelIterator)                  \
        *pixelIterator = color;

Texture *createTexture(int width, int height, int bytesPerPixel, unsigned int colorFill)
{
    Texture *out = (Texture *)malloc(sizeof(Texture));

    if (out == NULL)
        goto fail_create_texture;

    out->width = width;
    out->height = height;
    out->bytesPerPixel = bytesPerPixel;
    out->totalPixels = width * height;
    out->totalBytes = out->totalPixels * bytesPerPixel;

    out->pixels = (unsigned int *)malloc(out->totalBytes);

    if (out->pixels == NULL)
        goto fail_create_texture;

    goto sucess_create_texture;

fail_create_texture:

    if (out)
        free(out);

    return NULL;

sucess_create_texture:
{
    fillTextureColor(*out, colorFill);
}
    return out;
}

Texture *extractSubTexture(int x, int y, int width, int height, Texture *src)
{
    if (src == NULL || x >= src->width || y >= src->height || width <= 0 || height <= 0)
        goto fail_to_extract_texture_slice;

    Texture *out = createTexture(width, height, 4, 0xFFFFFFFF);

    if (out == NULL)
        goto fail_to_extract_texture_slice;

    for (int Y = 0; Y < height; ++Y)
    {
        for (int X = 0; X < width; ++X)
        {
            int txIndexSrc = ((Y + y) % src->height) * src->width + ((x + X) % src->width);
            int txIndexDst = Y * width + X;
            out->pixels[txIndexDst] = src->pixels[txIndexSrc];
        }
    }

    return out;

fail_to_extract_texture_slice:
    return NULL;
}

/**
 * @brief Draws a texture onto the framebuffer at the specified coordinates.
 *
 * This function blits the provided texture onto the framebuffer, starting
 * from the top-left corner (x, y). The texture will be clipped if it extends
 * beyond the screen boundaries.
 *
 * @param x The X coordinate on the screen where the texture's top-left corner will be drawn.
 * @param y The Y coordinate on the screen where the texture's top-left corner will be drawn.
 * @param texture A pointer to the Texture to be drawn. If NULL, the function will return immediately.
 *
 * @details
 * - If the texture is partially or fully off-screen, it will be clipped to fit within the screen.
 * - The function returns immediately if the texture has invalid dimensions (width <= 0 or height <= 0).
 *
 * @note This function assumes that the framebuffer is a global `uint32_t` array, and the screen dimensions are stored in `gScreenWidth` and `gScreenHeight`.
 */
static inline void drawTexture(int x, int y, Texture *texture)
{
    if (!texture || texture->width <= 0 || texture->height <= 0)
        return;

    int width = texture->width;
    int height = texture->height;
    int x2 = x + width;
    int y2 = y + height;

    // Ensure the texture is within screen bounds
    if (x >= gScreenWidth || y >= gScreenHeight || x2 <= 0 || y2 <= 0)
        return;

    // Calculate starting points in the texture and framebuffer
    int tx_start = (x < 0) ? -x : 0;
    int ty_start = (y < 0) ? -y : 0;
    int fx_start = (x < 0) ? 0 : x;
    int fy_start = (y < 0) ? 0 : y;

    int tx_end = (x2 > gScreenWidth) ? width - (x2 - gScreenWidth) : width;
    int ty_end = (y2 > gScreenHeight) ? height - (y2 - gScreenHeight) : height;

    // Initialize pixel iterators
    uint32_t *texturePixelsIterator = &texture->pixels[ty_start * width + tx_start];
    uint32_t *framebufferPixelsIterator = &framebuffer[fy_start * gScreenWidth + fx_start];

    // Calculate the row width to copy
    int row_width = tx_end - tx_start;

    do
    {
        uint32_t *textureRowPixelsIterator = texturePixelsIterator;
        uint32_t *framebufferRowPixelsIterator = framebufferPixelsIterator;

        do
        {
            *framebufferRowPixelsIterator++ = *textureRowPixelsIterator++;
        } while (--row_width > 0);

        texturePixelsIterator += width;
        framebufferPixelsIterator += gScreenWidth;

        row_width = tx_end - tx_start; // Reset row width for the next row
    } while (framebufferPixelsIterator < &framebuffer[fy_start * gScreenWidth + (ty_end - ty_start) * gScreenWidth]);
}

/**
 * @brief Draws a texture onto the framebuffer at the specified coordinates with a custom size.
 *
 * This function scales the provided texture to the specified width and height,
 * and then blits it onto the framebuffer at the given coordinates.
 *
 * @param x The X coordinate on the screen where the texture's top-left corner will be drawn.
 * @param y The Y coordinate on the screen where the texture's top-left corner will be drawn.
 * @param texture A pointer to the Texture to be drawn. If NULL, the function will return immediately.
 * @param targetWidth The desired width of the texture on the screen.
 * @param targetHeight The desired height of the texture on the screen.
 *
 * @details
 * - If the texture is partially or fully off-screen, it will be clipped to fit within the screen.
 * - The function uses nearest-neighbor scaling to draw the texture at the specified size.
 * - The function returns immediately if the texture has invalid dimensions (width <= 0, height <= 0, targetWidth <= 0, targetHeight <= 0).
 */
static inline void drawScaledTexture(int x, int y, Texture *texture, int targetWidth, int targetHeight)
{
    if (!texture || texture->width <= 0 || texture->height <= 0 || targetWidth <= 0 || targetHeight <= 0)
        return;

    int x2 = x + targetWidth;
    int y2 = y + targetHeight;

    // Ensure the texture is within screen bounds
    if (x >= gScreenWidth || y >= gScreenHeight || x2 <= 0 || y2 <= 0)
        return;

    int x1 = x > 0 ? x : 0;
    int y1 = y > 0 ? y : 0;

    x2 = (x2 < gScreenWidth) ? x2 : gScreenWidth;
    y2 = (y2 < gScreenHeight) ? y2 : gScreenHeight;

    double scaleX = (double)texture->width / targetWidth;
    double scaleY = (double)texture->height / targetHeight;

    double tx_start = (x < 0) ? -x * scaleX : 0.0;
    double ty_start = (y < 0) ? -y * scaleY : 0.0;

    double txIterator = tx_start;
    double tyIterator = ty_start;

    for (int Y = y1; Y < y2; ++Y)
    {
        txIterator = tx_start;
        for (int X = x1; X < x2; ++X)
        {
            uint32_t txColor = texture->pixels[(int)tyIterator * texture->width + (int)txIterator];

            framebuffer[Y * gScreenWidth + X] = txColor;

            txIterator += scaleX;
        }
        tyIterator += scaleY;
    }
}

/**
 * @brief Draws a texture onto the framebuffer at the specified coordinates with a custom size using bilinear filtering.
 *
 * This function scales the provided texture to the specified width and height,
 * and then blits it onto the framebuffer at the given coordinates using bilinear filtering.
 *
 * @param x The X coordinate on the screen where the texture's top-left corner will be drawn.
 * @param y The Y coordinate on the screen where the texture's top-left corner will be drawn.
 * @param texture A pointer to the Texture to be drawn. If NULL, the function will return immediately.
 * @param targetWidth The desired width of the texture on the screen.
 * @param targetHeight The desired height of the texture on the screen.
 *
 * @details
 * - If the texture is partially or fully off-screen, it will be clipped to fit within the screen.
 * - The function uses bilinear filtering to draw the texture at the specified size.
 * - The function returns immediately if the texture has invalid dimensions (width <= 0, height <= 0, targetWidth <= 0, targetHeight <= 0).
 */
static inline void drawBilinearScaledTexture(int x, int y, Texture *texture, int targetWidth, int targetHeight)
{
    if (!texture || texture->width <= 0 || texture->height <= 0 || targetWidth <= 0 || targetHeight <= 0)
        return;

    int x2 = x + targetWidth;
    int y2 = y + targetHeight;

    // Ensure the texture is within screen bounds
    if (x >= gScreenWidth || y >= gScreenHeight || x2 <= 0 || y2 <= 0)
        return;

    int x1 = x > 0 ? x : 0;
    int y1 = y > 0 ? y : 0;

    x2 = (x2 < gScreenWidth) ? x2 : gScreenWidth;
    y2 = (y2 < gScreenHeight) ? y2 : gScreenHeight;

    double scaleX = (double)texture->width / targetWidth;
    double scaleY = (double)texture->height / targetHeight;

    for (int Y = y1; Y < y2; ++Y)
    {
        // Calculate the texture Y coordinate
        double ty = (Y - y) * scaleY;
        int ty1 = (int)ty;
        int ty2 = ty1 + 1;
        double dy = ty - ty1;

        if (ty1 < 0)
            ty1 = 0;
        if (ty2 >= texture->height)
            ty2 = texture->height - 1;

        for (int X = x1; X < x2; ++X)
        {
            // Calculate the texture X coordinate
            double tx = (X - x) * scaleX;
            int tx1 = (int)tx;
            int tx2 = tx1 + 1;
            double dx = tx - tx1;

            if (tx1 < 0)
                tx1 = 0;
            if (tx2 >= texture->width)
                tx2 = texture->width - 1;

            // Get the four surrounding pixels
            uint32_t c00 = texture->pixels[ty1 * texture->width + tx1];
            uint32_t c01 = texture->pixels[ty1 * texture->width + tx2];
            uint32_t c10 = texture->pixels[ty2 * texture->width + tx1];
            uint32_t c11 = texture->pixels[ty2 * texture->width + tx2];

            // Decompose colors into RGB components
            uint8_t r00 = (c00 >> 16) & 0xFF;
            uint8_t g00 = (c00 >> 8) & 0xFF;
            uint8_t b00 = c00 & 0xFF;

            uint8_t r01 = (c01 >> 16) & 0xFF;
            uint8_t g01 = (c01 >> 8) & 0xFF;
            uint8_t b01 = c01 & 0xFF;

            uint8_t r10 = (c10 >> 16) & 0xFF;
            uint8_t g10 = (c10 >> 8) & 0xFF;
            uint8_t b10 = c10 & 0xFF;

            uint8_t r11 = (c11 >> 16) & 0xFF;
            uint8_t g11 = (c11 >> 8) & 0xFF;
            uint8_t b11 = c11 & 0xFF;

            // Interpolate between the four surrounding pixels
            uint8_t rX1 = (uint8_t)(r00 + (r01 - r00) * dx);
            uint8_t gX1 = (uint8_t)(g00 + (g01 - g00) * dx);
            uint8_t bX1 = (uint8_t)(b00 + (b01 - b00) * dx);

            uint8_t rX2 = (uint8_t)(r10 + (r11 - r10) * dx);
            uint8_t gX2 = (uint8_t)(g10 + (g11 - g10) * dx);
            uint8_t bX2 = (uint8_t)(b10 + (b11 - b10) * dx);

            uint8_t rFinal = (uint8_t)(rX1 + (rX2 - rX1) * dy);
            uint8_t gFinal = (uint8_t)(gX1 + (gX2 - gX1) * dy);
            uint8_t bFinal = (uint8_t)(bX1 + (bX2 - bX1) * dy);

            // Reassemble the color into a uint32_t
            uint32_t finalColor = (rFinal << 16) | (gFinal << 8) | bFinal;

            framebuffer[Y * gScreenWidth + X] = finalColor;
        }
    }
}

/**
 * @brief Draws a subtexture from the source texture onto the framebuffer at the specified coordinates.
 *
 * This function blits a rectangular portion (subtexture) from the source texture onto the framebuffer,
 * starting from the top-left corner (x, y). The subtexture will be clipped if it extends beyond the screen boundaries.
 *
 * @param x The X coordinate on the screen where the subtexture's top-left corner will be drawn.
 * @param y The Y coordinate on the screen where the subtexture's top-left corner will be drawn.
 * @param srcX The X coordinate in the source texture where the subtexture starts.
 * @param srcY The Y coordinate in the source texture where the subtexture starts.
 * @param subWidth The width of the subtexture to be drawn.
 * @param subHeight The height of the subtexture to be drawn.
 * @param texture A pointer to the source Texture from which the subtexture will be extracted and drawn.
 *
 * @details
 * - If the subtexture is partially or fully off-screen, it will be clipped to fit within the screen.
 * - The function returns immediately if the subtexture has invalid dimensions or if the source texture is NULL.
 *
 * @note This function assumes that the framebuffer is a global `uint32_t` array, and the screen dimensions are stored in `gScreenWidth` and `gScreenHeight`.
 */
static inline void drawSubTexture(int x, int y, int srcX, int srcY, int subWidth, int subHeight, Texture *texture)
{
    if (!texture || subWidth <= 0 || subHeight <= 0 || srcX >= texture->width || srcY >= texture->height)
        return;

    int x2 = x + subWidth;
    int y2 = y + subHeight;

    // Ensure the subtexture is within screen bounds
    if (x >= gScreenWidth || y >= gScreenHeight || x2 <= 0 || y2 <= 0)
        return;

    // Calculate starting points in the subtexture and framebuffer
    int tx_start = (x < 0) ? -x : 0;
    int ty_start = (y < 0) ? -y : 0;
    int fx_start = (x < 0) ? 0 : x;
    int fy_start = (y < 0) ? 0 : y;

    int tx_end = (x2 > gScreenWidth) ? subWidth - (x2 - gScreenWidth) : subWidth;
    int ty_end = (y2 > gScreenHeight) ? subHeight - (y2 - gScreenHeight) : subHeight;

    // Initialize pixel iterators
    uint32_t *texturePixelsIterator = &texture->pixels[(ty_start + srcY) * texture->width + (tx_start + srcX)];
    uint32_t *framebufferPixelsIterator = &framebuffer[fy_start * gScreenWidth + fx_start];

    // Calculate the row width to copy
    int row_width = tx_end - tx_start;

    do
    {
        uint32_t *textureRowPixelsIterator = texturePixelsIterator;
        uint32_t *framebufferRowPixelsIterator = framebufferPixelsIterator;

        do
        {
            *framebufferRowPixelsIterator++ = *textureRowPixelsIterator++;
        } while (--row_width > 0);

        texturePixelsIterator += texture->width;
        framebufferPixelsIterator += gScreenWidth;

        row_width = tx_end - tx_start; // Reset row width for the next row
    } while (framebufferPixelsIterator < &framebuffer[fy_start * gScreenWidth + (ty_end - ty_start) * gScreenWidth]);
}

/**
 * @brief Draws a scaled subtexture onto the framebuffer at the specified coordinates.
 *
 * This function scales a subtexture to the specified width and height and then draws it onto the framebuffer
 * at the given coordinates using nearest-neighbor scaling.
 *
 * @param x The X coordinate on the screen where the subtexture's top-left corner will be drawn.
 * @param y The Y coordinate on the screen where the subtexture's top-left corner will be drawn.
 * @param srcTexture A pointer to the source Texture containing the subtexture.
 * @param subX The X coordinate of the subtexture within the source texture.
 * @param subY The Y coordinate of the subtexture within the source texture.
 * @param subWidth The width of the subtexture to be extracted.
 * @param subHeight The height of the subtexture to be extracted.
 * @param targetWidth The desired width of the subtexture on the screen.
 * @param targetHeight The desired height of the subtexture on the screen.
 *
 * @details
 * - This function uses nearest-neighbor scaling to draw the subtexture.
 * - It directly accesses the pixel data of the source texture.
 */
static inline void drawScaledSubTexture(int x, int y, Texture *srcTexture, int subX, int subY, int subWidth, int subHeight, int targetWidth, int targetHeight)
{
    if (!srcTexture || subWidth <= 0 || subHeight <= 0 || targetWidth <= 0 || targetHeight <= 0)
        return;

    uint32_t *srcPixels = srcTexture->pixels;
    int srcTextureWidth = srcTexture->width;
    int srcTextureHeight = srcTexture->height;

    // Calculate scaling factors
    float xScale = (float)subWidth / targetWidth;
    float yScale = (float)subHeight / targetHeight;

    for (int ty = 0; ty < targetHeight; ++ty)
    {
        for (int tx = 0; tx < targetWidth; ++tx)
        {
            int srcX = subX + (int)(tx * xScale);
            int srcY = subY + (int)(ty * yScale);

            if (srcX >= subX + subWidth)
                srcX = subX + subWidth - 1;
            if (srcY >= subY + subHeight)
                srcY = subY + subHeight - 1;

            uint32_t color = srcPixels[srcY * srcTextureWidth + srcX];
            framebuffer[(y + ty) * gCorrectPixelsWidth + (x + tx)] = color;
        }
    }
}

static inline Texture *loadTextureFromImageFile(const char *filename)
{
    Raster8888 *imageRaster = loadBMP(filename);

    if (imageRaster == NULL)
        return NULL;

    Texture *out = createTexture(imageRaster->width, imageRaster->height, 4, 0x00000000);

    memcpy(out->pixels, imageRaster->pixels, out->totalBytes);

    return out;
}

void releaseTextureResources(Texture *texture)
{
    if (texture == NULL)
        return;

    if (texture->pixels)
        free(texture->pixels);

    free(texture);
}

#endif