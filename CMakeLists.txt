cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

project(HenigmaEngine)

add_subdirectory(lib/glfw)
add_subdirectory(lib/fmt)

add_library(${PROJECT_NAME}
lib/matematika/matematika.cpp
lib/glad/src/glad.c
src/barva.cpp
src/font.cpp
src/risalnik.cpp
src/objekt.cpp
src/ploscice.cpp
src/zvok.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC
lib/glad/include/
lib/glfw/include/
lib/fmt/include/
lib/miniaudio/
lib/
)

target_link_libraries(${PROJECT_NAME}
glfw
opengl32
fmt
)