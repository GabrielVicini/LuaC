#include "lua_engine.h"
#include "LuaGraphics.h"
#include "LuaSystem.h"
#include <stdio.h>

lua_State* LuaEngine_Create() {
    lua_State *L = luaL_newstate();
    luaL_requiref(L, "_G", luaopen_base, 1);
    luaL_requiref(L, "math", luaopen_math, 1);
    luaL_requiref(L, "string", luaopen_string, 1);
    luaL_requiref(L, "table", luaopen_table, 1);
    luaL_requiref(L, "utf8", luaopen_utf8, 1);
    luaL_requiref(L, "coroutine", luaopen_coroutine, 1);
    GraphicsRegister(L);
    SystemRegister(L);
    return L;
}

void LuaEngine_Destroy(lua_State *L) {
    lua_close(L);
}

void LuaEngine_RunStartup(lua_State *L) {
    if (luaL_dofile(L, "lua/rom/bios.lua") != LUA_OK) {
        printf("Lua error: %s\n", lua_tostring(L, -1));
        lua_pop(L, 1);
    }
}

void LuaEngine_Update(lua_State *L) {
    lua_getglobal(L, "update");
    if (lua_isfunction(L, -1)) {
        if (lua_pcall(L, 0, 0, 0) != LUA_OK) {
            printf("Lua error in update(): %s\n", lua_tostring(L, -1));
            lua_pop(L, 1);
        }
    } else {
        lua_pop(L, 1);
    }
}
