#include "lua_engine.h"
#include "LuaGraphics.h"
#include "LuaSystem.h"
#include <stdio.h>

static lua_State* update_thread = NULL;
static double update_thread_wake = 0.0;

lua_State* LuaEngine_Create() {
    lua_State *L = luaL_newstate();
    luaL_requiref(L, "_G", luaopen_base, 1);
    luaL_requiref(L, "math", luaopen_math, 1);
    luaL_requiref(L, "string", luaopen_string, 1);
    luaL_requiref(L, "table", luaopen_table, 1);
    luaL_requiref(L, "utf8", luaopen_utf8, 1);
    luaL_requiref(L, "coroutine", luaopen_coroutine, 1);
    luaL_requiref(L, "package", luaopen_package, 1);
    luaL_requiref(L, "os", luaopen_package, 1);
    lua_pop(L, 1); // because luaL_requiref leaves it on the stack
    GraphicsRegister(L);
    SystemRegister(L);
    return L;
}

void LuaEngine_Destroy(lua_State *L) {
    lua_close(L);
}

void LuaEngine_RunStartup(lua_State *L) {
    if (luaL_dofile(L, "lua/rom/kernel.lua") != LUA_OK) {
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

    int nresults = 0;
    int status = lua_resume(update_thread, NULL, 0, &nresults);

    if (status == LUA_YIELD) {
        if (nresults < 1 || !lua_isnumber(update_thread, -1)) {
            printf("wait() did not yield a numeric wake time (nresults=%d)\n", nresults);
            lua_pop(update_thread, nresults);
            update_thread_wake = now;
        } else {
            update_thread_wake = lua_tonumber(update_thread, -1);
            lua_pop(update_thread, nresults);
        }
        return;
    }

    if (status == LUA_OK) {
        if (nresults > 0) lua_pop(update_thread, nresults);
        printf("update coroutine finished.\n");
        update_thread = NULL;
        return;
    }
    const char *err = lua_tostring(update_thread, -1);
    printf("Lua error in update coroutine: %s\n", err ? err : "(unknown)");
    lua_pop(update_thread, 1);

    update_thread = NULL;
}
