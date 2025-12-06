#include "raylib.h"
#include "engine/render_buffer.h"
#include "engine/lua_engine.h"

#include "lua/LuaGraphics.h"
#include "lua/LuaSystem.h"
#include "lua/LuaKeyboard.h"

int main(void)
{
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(620, 360, "RetroC");

    const char *iconFile = "../resources/assets/icon.png";
    Image icon = LoadImage(iconFile);
    SetWindowIcon(icon);
    UnloadImage(icon);

    lua_State *L = LuaEngine_Create();

    const int fbWidth = 620;
    const int fbHeight = 360;
    Framebuffer fb = Framebuffer_Create(fbWidth, fbHeight);
    Framebuffer_Clear(&fb, BLACK);

    GraphicsInit(&fb);
    SystemInit(&fb);

    LuaEngine_RunStartup(L);

    SetTargetFPS(120);

    while (!WindowShouldClose()) {

        LuaEngine_Update(L);

        BeginDrawing();
        ClearBackground(BLACK);

        Framebuffer_Render(&fb, GetScreenWidth(), GetScreenHeight());
        EndDrawing();
    }


    LuaEngine_Destroy(L);
    Framebuffer_Destroy(&fb);
    CloseWindow();
    return 0;
}
