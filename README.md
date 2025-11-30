# LuaC

A small experimental “fake OS” environment built in C.  
This project embeds a Lua VM, uses Raylib for window/input handling, and renders everything through a software framebuffer.

This is my first project written in C, so expect bugs, incomplete systems, and rough edges.

---

## Overview
LuaC creates a simple virtual computer environment:

- A framebuffer drawn entirely in software  
- A Lua-based “kernel” that runs each frame  
- A minimal C→Lua API for graphics, keyboard, and mouse  
- A custom text renderer  
- UTF-8 character input  
- Raylib handling window creation and event polling  

Everything you see on screen is drawn pixel-by-pixel by the Lua script using the exposed API.


---

## Features
*(intentionally left empty)*

---

## Build Requirements
- CMake 3.10 or newer  
- Raylib 5.x  
- Lua 5.4.8 (compiled from source)  
- A C compiler (MinGW, MSVC, Clang, etc.)
**Personally, I dont know much about C compilers; But i use Clion with CMake and MinGW. And I'm using C11**
