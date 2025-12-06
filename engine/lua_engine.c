#include "lua_engine.h"
#include "../lua/LuaGraphics.h"
#include "../lua/LuaSystem.h"
#include <stdio.h>

static lua_State* update_thread = NULL;
static double update_thread_wake = 0.0;

lua_State* LuaEngine_Create() {
    lua_State *L = luaL_newstate();
    luaL_openlibs(L);
    GraphicsRegister(L);
    SystemRegister(L);
    return L;
}


void LuaEngine_Destroy(lua_State *L) {
    lua_close(L);
}

void LuaEngine_RunStartup(lua_State *L) {
    if (luaL_dofile(L, "resources/rom/kernel.lua") != LUA_OK) {
        const char *err = lua_tostring(L, -1);
        printf("Lua BIOS error: %s\n", err);
        lua_pop(L, 1);

        return;
    }

    update_thread = lua_newthread(L);

    lua_getglobal(update_thread, "main");
    if (!lua_isfunction(update_thread, -1)) {
        printf("No global 'main' function defined in bios.lua\n");
        lua_pop(update_thread, 1);
        update_thread = NULL;
        return;
    }

    update_thread_wake = 0.0;
}



void LuaEngine_Update(lua_State *L) {
    (void)L;

    if (!update_thread) {
        return;
    }

    double now = GetTime();
    if (now < update_thread_wake) {
        return;
    }

    // LuaJIT: lua_resume(thread, nargs)
    int status = lua_resume(update_thread, 0);
    int nresults = lua_gettop(update_thread);  // how many values are on the stack

    if (status == LUA_YIELD) {
        if (nresults < 1 || !lua_isnumber(update_thread, -1)) {
            printf("wait() did not yield a numeric wake time (nresults=%d)\n", nresults);
            lua_settop(update_thread, 0);
            update_thread_wake = now;
        } else {
            update_thread_wake = lua_tonumber(update_thread, -1);
            lua_settop(update_thread, 0);
        }
        return;
    }

    if (status == LUA_OK || status == 0) {
        if (nresults > 0) lua_settop(update_thread, 0);
        printf("update coroutine finished.\n");
        update_thread = NULL;
        return;
    }

    const char *err = lua_tostring(update_thread, -1);
    printf("Lua error in update coroutine: %s\n", err ? err : "(unknown)");
    lua_settop(update_thread, 0);
    update_thread = NULL;
}
