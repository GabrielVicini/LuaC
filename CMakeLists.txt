cmake_minimum_required(VERSION 3.10)
project(LuaC C)

set(CMAKE_C_STANDARD 11)

set(RAYLIB_PATH "C:/Libraries/raylib")
set(LUA_PATH    "C:/Libraries/lua-5.4.8/src")

link_directories(${RAYLIB_PATH}/lib)

file(COPY "lua/rom" DESTINATION "${CMAKE_BINARY_DIR}/lua")

file(GLOB LUA_SOURCES
        "${LUA_PATH}/*.c"
)

list(REMOVE_ITEM LUA_SOURCES
        "${LUA_PATH}/lua.c"
        "${LUA_PATH}/luac.c"
)

add_executable(LuaC
        main.c
        engine/render_buffer.c
        engine/dev_tools.c
        engine/lua_engine.c
        lua/library/keyboard.c
        ${LUA_SOURCES}
)

target_include_directories(LuaC PUBLIC
        ${RAYLIB_PATH}/include
        ${LUA_PATH}
        ${CMAKE_SOURCE_DIR}
        ${CMAKE_SOURCE_DIR}/engine
        ${CMAKE_SOURCE_DIR}/lua/library
)
# sdfsf
target_link_libraries(LuaC
        raylib
        opengl32
        gdi32
        winmm
)
