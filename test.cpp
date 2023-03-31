#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <freetype2/freetype/config/ftheader.h>
#include <freetype2/ft2build.h>
#include <glm/glm.hpp>
#include FT_FREETYPE_H
void posodobiOkno(GLFWwindow *okno, int width, int height);
class Znak
{
public:
    uint textura;
    glm::ivec2 velikost;
    glm::ivec2 zamik;
    uint zamikNaslednjega;

private:
};
class Pisava
{
public:
    Pisava(const char *potDoPisave, int velikost)
    {
        FT_Library ft;
        if (FT_Init_FreeType(&ft))
        {
            std::cout << "ni free type" << std::endl;
            std::exit(-1);
        }
        FT_Face face;
        if (FT_New_Face(ft, potDoPisave, 0, &face))
        {
            std::cout << "ni obraza" << std::endl;
            std::exit(-1);
        }
        FT_Set_Pixel_Sizes(face, 0, velikost);
        for (char c = '\0'; c < 255; c++)
        {
            uint textura;
            glGenTextures(1, &textura);
            glBindTexture(GL_TEXTURE_2D, textura);
        }
    }

private:
};
int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *okno = glfwCreateWindow(800, 600, "Pozdravljen svet!", NULL, NULL);

    if (okno == nullptr)
    {
        std::cout << "NI OKNA";
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(okno);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "NI GLADA";
        return -1;
    }
    glViewport(0, 0, 800, 600);
    glfwSetFramebufferSizeCallback(okno, posodobiOkno);

    while (!glfwWindowShouldClose(okno))
    {
        glClearColor(0.3, 0.2, 0.4, 1);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(okno);
        glfwPollEvents();
    }
    glfwTerminate();
}
void posodobiOkno(GLFWwindow *okno, int width, int height)
{
    glViewport(0, 0, width, height);
}
