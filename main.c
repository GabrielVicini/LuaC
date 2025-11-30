#include "raylib.h"
#include "engine/render_buffer.h"
#include "engine/lua_engine.h"
#include "lua/library/LuaGraphics.h"

int main(void)
{
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(620, 360, "LuaC");

    lua_State *L = LuaEngine_Create();

    const int fbWidth = 620;
    const int fbHeight = 360;
    Framebuffer fb = Framebuffer_Create(fbWidth, fbHeight);
    Framebuffer_Clear(&fb, BLACK);

    GraphicsInit(&fb);

    LuaEngine_RunStartup(L);

    SetTargetFPS(120);
    int t = 0;

    while (!WindowShouldClose()) {

        LuaEngine_Update(L);

        BeginDrawing();
        ClearBackground(BLACK);
        // DebugScreen1(&fb);

        Framebuffer_Render(&fb, GetScreenWidth(), GetScreenHeight());
        EndDrawing();
    }


    LuaEngine_Destroy(L);
    Framebuffer_Destroy(&fb);
    CloseWindow();
    return 0;
}
