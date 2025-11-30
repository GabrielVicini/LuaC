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

Now, I will proabbly upload some templayes to help people get started but that's much later.

Everything on the screen is drawn pixel-by-pixel by Lua code using the exposed C API.

![202511301038](https://github.com/user-attachments/assets/c534417f-82e3-4f7e-93db-d18d550f20b4)


---

## Features
*(intentionally left empty)*

---

## Build Requirements
idk yet
