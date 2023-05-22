cmake_minimum_required(VERSION 3.20)

project(a)

add_executable(${PROJECT_NAME}
        ../src/test.cpp
        ../src/glad/src/glad.c
        ../src/Render/Render.cpp
        ../src/ostalo/ostalo.cpp
)

include_directories(${PROJECT_NAME}
        src/glad/include/
        /usr/include/freetype2 
        /usr/include/freetype2/config
        src/glfw/include/GLFW
)

target_link_libraries(${PROJECT_NAME} PRIVATE
        glfw
        GL 
        fmt 
        freetype
)
add_subdirectory(src/glfw/)



