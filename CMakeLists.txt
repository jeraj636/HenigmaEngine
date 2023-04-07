cmake_minimum_required(VERSION 3.20)

project(a)

add_executable(${PROJECT_NAME}
        test.cpp
        glad/src/glad.c
        ostalo/ostalo.cpp
        renderer/renderer.cpp
        podEnote/scena/scena.cpp
        podEnote/skupina/skupina.cpp
        objekt/objekt.cpp
        komponente/upodabljalnik/upodabljalnik.cpp
        komponente/transformacija/transformacija.cpp
        komponente/gumb/gumb.cpp
        komponente/komponenta.cpp
        matematika/matematika.cpp
)

include_directories(${PROJECT_NAME}
        glad/include/

)

target_link_libraries(${PROJECT_NAME} PRIVATE
        glfw
        GL 
        fmt 
        freetype
)

set(FREETYPE_INCLUDE_DIRS "/usr/include/freetype2")
set(FREETYPE_LIBRARIES "/usr/lib/x86_64-linux-gnu/libfreetype.so")

set(FREETYPE_DIR "/usr/include/freetype2")
include_directories(${FREETYPE_DIR})


