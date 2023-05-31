cmake_minimum_required(VERSION 3.20)

project(HenigmaEngine)

#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
#set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
#set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

add_library(${PROJECT_NAME}
        src/glad/src/glad.c
        src/Render/Render.cpp
        src/Render/Font.cpp
        src/Render/Risalnik.cpp
        src/Render/Scene.cpp
        src/ostalo/ostalo.cpp
        src/Matematika/Matematika.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC
        src/glad/include/
        /usr/include/freetype2 
        /usr/include/freetype2/config
        src/glfw/include/GLFW
)

target_link_libraries(${PROJECT_NAME} PUBLIC
        glfw
        GL 
        fmt 
        freetype
)
add_subdirectory(src/glfw/)



