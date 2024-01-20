cmake_minimum_required(VERSION 3.20)

project(HenigmaEngine)

add_subdirectory(lib/glfw)
add_subdirectory(lib/fmt)

add_executable(${PROJECT_NAME}
../lib/matematika/matematika.cpp
../lib/glad/src/glad.c
../src/barva.cpp
../src/font.cpp
../src/main.cpp
../src/risalnik.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE
lib/glad/include/
lib/glfw/include/
lib/fmt/include/
lib/
)

target_link_libraries(${PROJECT_NAME}
glfw
GL
fmt
)