# Lua

A small experimental “fake OS” environment built in C.  
This project embeds a Lua VM, uses Raylib for window/input handling, and renders everything through a software framebuffer.

This is my first project written in C, so expect bugs, incomplete systems, and rough edges.

---

## Overview
LuaC creates a minimal virtual computer environment.

The core design philosophy is simple: **everything is done in Lua**.  
Unlike alternatives such as CraftOS-PC, LuaC does not provide high-level helpers or shortcuts.  

You are expected to implement your own text rendering, UI, and higher-level systems entirely in Lua using the low-level pixel API, there are some other graphic functions such as lines and regtangles because of performance concern. (Clearing the screen shouldn't take 20,000 API calls)

[RaytracingTest](https://github.com/user-attachments/assets/0eb6ed60-ff40-4b04-bc51-cd262a22981f)

![FirstGraphicsDemo](https://github.com/user-attachments/assets/c534417f-82e3-4f7e-93db-d18d550f20b4)

---

## Build Requirements
idk yet
