cmake_minimum_required(VERSION 3.20)

project(HenigmaEngine)

add_subdirectory(src/glfw/)

add_executable(${PROJECT_NAME}
    ../src/test.cpp 
    ../src/Risalnik/Risalnik.cpp
    ../src/Risalnik/CallBack.cpp
    ../src/glad/src/glad.c 
    ../src/Matematika/Matematika.cpp
    ../src/Font/Font.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC 
        src/glad/include/
        src/glfw/include/
        /usr/include/freetype2 
        /usr/include/freetype2/config
)

target_link_libraries(${PROJECT_NAME} PUBLIC
        glfw
        GL 
        fmt 
        freetype
)