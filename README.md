# RetroC 
(I will change the name soon because RetroC is the same name as the offical Lua compiler and it makes error debuging really confusing)

## DANGER, DO NOT USE THIS PROJECT**
**It is not in a usable on your own state yet, check back in a few weeks.***

A small experimental “fake OS” environment built in C.  
This project embeds a Lua VM, uses Raylib for window/input handling, and renders everything through a software framebuffer.

This is my first project written in C, so expect bugs, incomplete systems, and rough edges.

---

## Overview
RetroC creates a minimal virtual computer environment.

The core design philosophy is simple: **everything is done in Lua**.  
Unlike alternatives such as CraftOS-PC, RetroC does not provide high-level helpers or shortcuts.  

You are expected to implement your own text rendering, UI, and higher-level systems entirely in Lua using the low-level pixel API, there are some other graphic functions such as lines and regtangles because of performance concern. (Clearing the screen shouldn't take 20,000 API calls)

[4DCube.webm](https://github.com/user-attachments/assets/b94ab337-7e7b-4691-9ffd-b6a164a6974b)

[RaytracingTest](https://github.com/user-attachments/assets/0eb6ed60-ff40-4b04-bc51-cd262a22981f)

(First graphics test, most APIS in this example don't exist anymore)
![FirstGraphicsDemo](https://github.com/user-attachments/assets/c534417f-82e3-4f7e-93db-d18d550f20b4)

---

## Build Requirements
idk yet
