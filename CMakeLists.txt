cmake_minimum_required(VERSION 3.10)
project(LuaC C)

set(CMAKE_C_STANDARD 11)

# --- Paths -------------------------------------------------------
# Change these if yours live somewhere else
set(RAYLIB_PATH      "C:/Libraries/raylib")
set(LUAJIT_SRC_PATH  "C:/Users/Gabriel/Desktop/LuaJIT/src")

# LuaJIT import library (built by `make` in that src dir)
set(LUAJIT_LIB       "${LUAJIT_SRC_PATH}/libluajit-5.1.dll.a")
set(LUAJIT_DLL       "${LUAJIT_SRC_PATH}/lua51.dll")

# --- Raylib libs dir ---------------------------------------------
link_directories(${RAYLIB_PATH}/lib)

# --- Copy Lua ROM into build dir (for your Lua files) ------------
file(COPY "lua/rom" DESTINATION "${CMAKE_BINARY_DIR}/lua")

# --- Our executable ----------------------------------------------
add_executable(LuaC
        main.c
        engine/render_buffer.c
        engine/lua_engine.c
        lua/library/LuaKeyboard.c
        lua/library/LuaGraphics.c
        lua/library/LuaSystem.c
)

# --- Include directories -----------------------------------------
target_include_directories(LuaC PUBLIC
        ${RAYLIB_PATH}/include
        ${LUAJIT_SRC_PATH}           # for lua.h, luajit.h, lauxlib.h, etc.
        ${CMAKE_SOURCE_DIR}
        ${CMAKE_SOURCE_DIR}/engine
        ${CMAKE_SOURCE_DIR}/lua/library
)

# --- Linking -----------------------------------------------------
if (WIN32)
    target_link_libraries(LuaC
            ${LUAJIT_LIB}        # link LuaJIT
            raylib
            opengl32
            gdi32
            winmm
    )
elseif (APPLE)
    target_link_libraries(LuaC
            ${LUAJIT_LIB}
            raylib
            "-framework OpenGL"
            "-framework Cocoa"
            "-framework IOKit"
            "-framework CoreVideo"
    )
else()  # Linux or other UNIX
    target_link_libraries(LuaC
            ${LUAJIT_LIB}
            raylib
            pthread
            m
            dl
            GL
            X11
            Xrandr
            Xi
    )
endif()

# --- Post-build: copy Lua ROM + LuaJIT DLL -----------------------
add_custom_command(
        TARGET LuaC POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/lua/rom"
        "${CMAKE_BINARY_DIR}/lua/rom"
)

# Copy lua51.dll next to the executable so it can actually load at runtime
if (WIN32)
    add_custom_command(
            TARGET LuaC POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${LUAJIT_DLL}"
            "$<TARGET_FILE_DIR:LuaC>"
    )
endif()
