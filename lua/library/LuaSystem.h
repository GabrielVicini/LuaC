#ifndef LuaSystem_h
#define LuaSystem_h

#include "lua.h"
#include "lauxlib.h"
#include "render_buffer.h"

void SystemInit(Framebuffer *fb);
void SystemRegister(lua_State *L);

#endif