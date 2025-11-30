#include "render_buffer.h"
#include "raylib.h"
#include <stdlib.h>
#include <stdio.h>

Framebuffer Framebuffer_Create(int w, int h) {
    Framebuffer fb;
    fb.width = w;
    fb.height = h;

    fb.pixels = malloc(w * h * sizeof(Color));

    for (int i = 0; i < w * h; i++)
        fb.pixels[i] = BLACK;


    Image img = GenImageColor(w, h, BLACK);


    fb.texture = LoadTextureFromImage(img);


    UnloadImage(img);

    return fb;
}




void Framebuffer_Destroy(Framebuffer *fb) {
    if (fb->pixels)
        free(fb->pixels);

    UnloadTexture(fb->texture);

    fb->pixels = NULL;
}

void Framebuffer_Resize(Framebuffer *fb, int newW, int newH) {

    UnloadTexture(fb->texture);


    free(fb->pixels);


    *fb = Framebuffer_Create(newW, newH);
}

void Framebuffer_Clear(Framebuffer *fb, Color c) {
    int total = fb->width * fb->height;
    for (int i = 0; i < total; i++)
        fb->pixels[i] = c;
}

void Framebuffer_SetPixel(Framebuffer *fb, int x, int y, Color c) {
    if (x < 0 || y < 0 || x >= fb->width || y >= fb->height)
        return;

    fb->pixels[y * fb->width + x] = c;
}

void Framebuffer_Render(Framebuffer *fb, int screenW, int screenH) {

    UpdateTexture(fb->texture, fb->pixels);


    Rectangle src = {
        0, 0,
        (float)fb->width,
        (float)fb->height
    };


    Rectangle dest = {
        0, 0,
        (float)screenW,
        (float)screenH
    };

    Vector2 origin = {0, 0};

    DrawTexturePro(
        fb->texture,
        src,
        dest,
        origin,
        0.0f,
        WHITE
    );
}
