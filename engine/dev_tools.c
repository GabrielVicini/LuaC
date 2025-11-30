#include "dev_tools.h"
#include "render_buffer.h"
#include "raylib.h"
#include <stdio.h>

void DevText(const char *msg, int x, int y) {
    DrawText(msg, x, y, 20, GREEN);
}

void DebugScreen1(Framebuffer *fb) {

    // draw borders
    for (int x = 0; x < fb->width; x++)
    {
        Framebuffer_SetPixel(fb, x, 0, RED);
        Framebuffer_SetPixel(fb, x, fb->height - 1, RED);
    }

    for (int y = 0; y < fb->height; y++)
    {
        Framebuffer_SetPixel(fb, 0, y, RED);
        Framebuffer_SetPixel(fb, fb->width - 1, y, RED);
    }

    // render framebuffer
    Framebuffer_Render(fb, GetScreenWidth(), GetScreenHeight());

    // debug text
    char buf[64];
    snprintf(buf, 64, "fb: %dx%d", fb->width, fb->height);
    DevText(buf, 10, 40);

    char wbuf[64];
    snprintf(wbuf, 64, "window: %dx%d", GetScreenWidth(), GetScreenHeight());
    DevText(wbuf, 10, 70);

    int scaleX = GetScreenWidth() / fb->width;
    int scaleY = GetScreenHeight() / fb->height;
    int scale = (scaleX < scaleY) ? scaleX : scaleY;
    if (scale < 1) scale = 1;

    char sbuf[64];
    snprintf(sbuf, 64, "scale: %d", scale);
    DevText(sbuf, 10, 100);
}