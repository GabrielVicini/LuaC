#ifndef LuaGraphics_h
#define LuaGraphics_h

#include "lua.h"
#include "lauxlib.h"
#include "render_buffer.h"

void GraphicsInit(Framebuffer *fb);
void GraphicsRegister(lua_State *L);

#endif