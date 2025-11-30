#include "render_buffer.h"
#include <stdio.h>
#include "raylib.h"
#include "LuaSystem.h"

static Framebuffer *g_fb = NULL;

void SystemInit(Framebuffer *fb) {
    g_fb = fb;
}

static int lua_sys_getTime(lua_State *L) {
    lua_pushnumber(L, GetTime()); // seconds as double
    return 1;
}

static int lua_sys_wait(lua_State *L) {
    double seconds = luaL_checknumber(L, 1);
    double wakeTime = GetTime() + seconds;

    lua_pushnumber(L, wakeTime);
    return lua_yield(L, 1);
}


void SystemRegister(lua_State *L) {
    lua_newtable(L);

    lua_pushcfunction(L, lua_sys_getTime);
    lua_setfield(L, -2, "getTime");

    lua_pushcfunction(L, lua_sys_wait);
    lua_setfield(L, -2, "wait");

    lua_setglobal(L, "sys");
}
