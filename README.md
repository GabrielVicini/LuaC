# LuaC

DANGER! THIS PROJECT IS NOT EVEN IN A USEABLE STATE YET. DO NOT USE UNLESS YOU ARE SURE WHAT YOU ARE DOING.

A small experimental “fake OS” environment built in C.  
This project embeds a Lua VM, uses Raylib for window/input handling, and renders everything through a software framebuffer.

This is my first project written in C, so expect bugs, incomplete systems, and rough edges.

---

## Overview
LuaC creates a minimal virtual computer environment.

The core design philosophy is simple: **everything is done in Lua**.  
Unlike alternatives such as CraftOS-PC, LuaC does not provide high-level helpers or shortcuts.  
You are expected to implement your own text rendering, UI, and higher-level systems entirely in Lua using the low-level pixel API.

Everything on the screen is drawn pixel-by-pixel by Lua code using the exposed C API.

<img width="600" height="397" alt="image" src="https://github.com/user-attachments/assets/98195523-461b-4a0f-b711-5629128a2676" />


---

## Features
*(intentionally left empty)*

---

## Build Requirements
- CMake 3.10 or newer  
- Raylib 5.x  
- Lua 5.4.8 (compiled from source)  
- A C compiler (MinGW, MSVC, Clang, etc.)

Personally, this project is built using **CLion**, **CMake**, **MinGW**, and **C11**, but any standard-compliant setup should work.
