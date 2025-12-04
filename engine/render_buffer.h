#ifndef RENDER_BUFFER_H
#define RENDER_BUFFER_H

#include "raylib.h"
#include <stddef.h>

typedef struct {
    int width;
    int height;
    Color *pixels;
    Texture2D texture;
} Framebuffer;

Framebuffer Framebuffer_Create(int w, int h);
void Framebuffer_Destroy(Framebuffer *fb);

void Framebuffer_Resize(Framebuffer *fb, int newW, int newH);

void Framebuffer_Clear(Framebuffer *fb, Color c);
void Framebuffer_SetPixel(Framebuffer *fb, int x, int y, Color c);

void Framebuffer_Render(Framebuffer *fb, int screenW, int screenH);

void Framebuffer_FillRect(Framebuffer *fb, int x, int y, int w, int h, Color c);
void Framebuffer_ScrollUp(Framebuffer *fb, int dy, Color clearColor);

void *my_memmove(void *dst, const void *src, size_t n);

#endif
