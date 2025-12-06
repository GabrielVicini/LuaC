cmake_minimum_required(VERSION 3.10)
project(RetroC C)

set(CMAKE_C_STANDARD 11)

set(RAYLIB_PATH      "C:/Libraries/raylib")
set(LUAJIT_SRC_PATH  "C:/Users/Gabriel/Desktop/LuaJIT/src")

set(LUAJIT_LIB       "${LUAJIT_SRC_PATH}/libluajit-5.1.dll.a")
set(LUAJIT_DLL       "${LUAJIT_SRC_PATH}/lua51.dll")

link_directories(${RAYLIB_PATH}/lib)

file(COPY "resources" DESTINATION "${CMAKE_BINARY_DIR}/resources")

add_executable(RetroC
        main.c
        engine/render_buffer.c
        engine/lua_engine.c
        lua/LuaKeyboard.c
        lua/LuaGraphics.c
        lua/LuaSystem.c
)

target_include_directories(RetroC PUBLIC
        ${RAYLIB_PATH}/include
        ${LUAJIT_SRC_PATH}           # for lua.h, luajit.h, lauxlib.h, etc.
        ${CMAKE_SOURCE_DIR}
        ${CMAKE_SOURCE_DIR}/engine
        ${CMAKE_SOURCE_DIR}/lua/library
)

if (WIN32)
    target_link_libraries(RetroC
            ${LUAJIT_LIB}        # link LuaJIT
            raylib
            opengl32
            gdi32
            winmm
    )
elseif (APPLE)
    target_link_libraries(RetroC
            ${LUAJIT_LIB}
            raylib
            "-framework OpenGL"
            "-framework Cocoa"
            "-framework IOKit"
            "-framework CoreVideo"
    )
else()  # Linux or other UNIX
    target_link_libraries(RetroC
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

add_custom_command(
        TARGET RetroC POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/resources"
        "${CMAKE_BINARY_DIR}/resources"
)

if (WIN32)
    add_custom_command(
            TARGET RetroC POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${LUAJIT_DLL}"
            "$<TARGET_FILE_DIR:RetroC>"
    )
endif()
