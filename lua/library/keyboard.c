#include "keyboard.h"
#include "render_buffer.h"
#include <stdio.h>
#include "raylib.h"

static Framebuffer *g_fb = NULL;

void LuaAPI_Init(Framebuffer *fb) {
    g_fb = fb;
}

static int lua_screen_setPixel(lua_State *L) {
    int x = luaL_checkinteger(L, 1);
    int y = luaL_checkinteger(L, 2);
    int r = luaL_checkinteger(L, 3);
    int g = luaL_checkinteger(L, 4);
    int b = luaL_checkinteger(L, 5);

    if (!g_fb) return 0;

    Color c = { (unsigned char)r, (unsigned char)g, (unsigned char)b, 255 };
    Framebuffer_SetPixel(g_fb, x, y, c);
    return 0;
}

static int lua_screen_clear(lua_State *L) {
    if (!g_fb) return 0;

    Color c = BLACK;

    if (lua_gettop(L) == 3) {
        int r = luaL_checkinteger(L, 1);
        int g = luaL_checkinteger(L, 2);
        int b = luaL_checkinteger(L, 3);
        c = (Color){ r, g, b, 255 };
    }

    Framebuffer_Clear(g_fb, c);
    return 0;
}

static int lua_keyboard_getKey(lua_State *L) {
    int key = GetKeyPressed();
    lua_pushinteger(L, key);
    return 1;
}

static int lua_keyboard_getChar(lua_State *L) {
    int key = GetKeyPressed();
    if (key == 0) {
        lua_pushinteger(L, 0);
        return 1;
    }

    if (key >= KEY_A && key <= KEY_Z) {
        bool shift = IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT);
        char c = (char)(key - KEY_A + (shift ? 'A' : 'a'));
        lua_pushlstring(L, &c, 1);
        return 1;
    }

    if (key >= KEY_ZERO && key <= KEY_NINE) {
        bool shift = IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT);

        static const char normal[]  = "0123456789";
        static const char shifted[] = ")!@#$%^&*(";

        int idx = key - KEY_ZERO;
        char c = shift ? shifted[idx] : normal[idx];
        lua_pushlstring(L, &c, 1);
        return 1;
    }

    if (key == KEY_SPACE) {
        lua_pushstring(L, " ");
        return 1;
    }

    if (key == KEY_ENTER) {
        lua_pushstring(L, "\n");
        return 1;
    }

    if (key == KEY_BACKSPACE) {
        lua_pushstring(L, "\b");
        return 1;
    }

    if (key == KEY_SLASH) {
        bool shift = IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT);
        char c = shift ? '?' : '/';
        lua_pushlstring(L, &c, 1);
        return 1;
    }

    lua_pushinteger(L, 0);
    return 1;
}

static int lua_mouse_getPosition(lua_State *L) {
    if (!g_fb) {
        lua_pushinteger(L, 0);
        lua_pushinteger(L, 0);
        return 2;
    }

    Vector2 pos = GetMousePosition();
    int screenW = GetScreenWidth();
    int screenH = GetScreenHeight();

    int x = 0;
    int y = 0;

    if (screenW > 0 && screenH > 0) {
        x = (int)(pos.x * (float)g_fb->width  / (float)screenW);
        y = (int)(pos.y * (float)g_fb->height / (float)screenH);
    }

    lua_pushinteger(L, x);
    lua_pushinteger(L, y);
    return 2;
}

static int lua_mouse_isDown(lua_State *L) {
    int button = luaL_checkinteger(L, 1);
    bool down = IsMouseButtonDown((MouseButton)button);
    lua_pushboolean(L, down);
    return 1;
}

static int lua_mouse_isPressed(lua_State *L) {
    int button = luaL_checkinteger(L, 1);
    bool pressed = IsMouseButtonPressed((MouseButton)button);
    lua_pushboolean(L, pressed);
    return 1;
}

static int lua_keyboard_isDown(lua_State *L) {
    int key = luaL_checkinteger(L, 1);
    bool down = IsKeyDown(key);
    lua_pushboolean(L, down);
    return 1;
}

static int lua_mouse_isReleased(lua_State *L) {
    int button = luaL_checkinteger(L, 1);
    bool released = IsMouseButtonReleased((MouseButton)button);
    lua_pushboolean(L, released);
    return 1;
}

static int lua_mouse_getWheelMove(lua_State *L) {
    float delta = GetMouseWheelMove();
    lua_pushnumber(L, delta);
    return 1;
}

static int lua_mouse_show(lua_State *L) {
    ShowCursor();
    return 0;
}

static int lua_mouse_hide(lua_State *L) {
    HideCursor();
    return 0;
}

static int lua_mouse_isHidden(lua_State *L) {
    lua_pushboolean(L, IsCursorHidden());
    return 1;
}

void LuaAPI_Register(lua_State *L) {
    lua_newtable(L);

    lua_newtable(L);
    lua_pushcfunction(L, lua_screen_setPixel);
    lua_setfield(L, -2, "setPixel");
    lua_pushcfunction(L, lua_screen_clear);
    lua_setfield(L, -2, "clear");
    lua_setfield(L, -2, "screen");

    lua_newtable(L);

    lua_pushinteger(L, KEY_BACKSPACE);
    lua_setfield(L, -2, "KEY_BACKSPACE");
    lua_pushinteger(L, KEY_ENTER);
    lua_setfield(L, -2, "KEY_ENTER");
    lua_pushinteger(L, KEY_SPACE);
    lua_setfield(L, -2, "KEY_SPACE");
    lua_pushinteger(L, KEY_A);
    lua_setfield(L, -2, "A");
    lua_pushinteger(L, KEY_Z);
    lua_setfield(L, -2, "Z");
    lua_pushinteger(L, KEY_ZERO);
    lua_setfield(L, -2, "ZERO");
    lua_pushinteger(L, KEY_NINE);
    lua_setfield(L, -2, "NINE");

    lua_pushcfunction(L, lua_keyboard_getKey);
    lua_setfield(L, -2, "getKey");
    lua_pushcfunction(L, lua_keyboard_getChar);
    lua_setfield(L, -2, "getChar");
    lua_pushcfunction(L, lua_keyboard_isDown);
    lua_setfield(L, -2, "isDown");

    lua_setfield(L, -2, "keyboard");

    lua_newtable(L);

    lua_pushcfunction(L, lua_mouse_getPosition);
    lua_setfield(L, -2, "getPosition");
    lua_pushcfunction(L, lua_mouse_isDown);
    lua_setfield(L, -2, "isDown");
    lua_pushcfunction(L, lua_mouse_isPressed);
    lua_setfield(L, -2, "isPressed");
    lua_pushcfunction(L, lua_mouse_isReleased);
    lua_setfield(L, -2, "isReleased");
    lua_pushcfunction(L, lua_mouse_getWheelMove);
    lua_setfield(L, -2, "getWheelMove");

    lua_pushinteger(L, MOUSE_BUTTON_LEFT);
    lua_setfield(L, -2, "BUTTON_LEFT");
    lua_pushinteger(L, MOUSE_BUTTON_RIGHT);
    lua_setfield(L, -2, "BUTTON_RIGHT");
    lua_pushinteger(L, MOUSE_BUTTON_MIDDLE);
    lua_setfield(L, -2, "BUTTON_MIDDLE");

    lua_pushcfunction(L, lua_mouse_show);
    lua_setfield(L, -2, "show");
    lua_pushcfunction(L, lua_mouse_hide);
    lua_setfield(L, -2, "hide");
    lua_pushcfunction(L, lua_mouse_isHidden);
    lua_setfield(L, -2, "isHidden");

    lua_setfield(L, -2, "mouse");

    lua_setglobal(L, "system");

    lua_getglobal(L, "system");
    lua_getfield(L, -1, "screen");
    lua_setglobal(L, "screen");
    lua_pop(L, 1);
}
