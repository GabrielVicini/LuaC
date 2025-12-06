#include "render_buffer.h"
#include <stdio.h>
#include "raylib.h"

static Framebuffer *g_fb = NULL;

void Keyboard_Init(Framebuffer *fb) {
    g_fb = fb;
}

