#ifndef LUA_API_H
#define LUA_API_H

#include "lua.h"
#include "lauxlib.h"
#include "render_buffer.h"

void Keyboard_Init(Framebuffer *fb);
void Keyboard_Register(lua_State *L);

#endif