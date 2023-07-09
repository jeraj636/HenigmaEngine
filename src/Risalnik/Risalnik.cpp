#include "../../Include/Risalnik.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "../../Include/Log.h"
void Risalnik::Init(const char *naslov)
{
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_okno = glfwCreateWindow(800, 600, naslov, NULL, NULL);
    if (m_okno == NULL)
    {
        glfwTerminate();
        io::err("NI OKNA");
    }
    io::msg("OKNO DELUJE");

    glfwMakeContextCurrent(m_okno);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        io::err("NI GLADA");
    }
    io::msg("GLAD DELA");

    glViewport(0, 0, 800, 600);

    NaloziCallBack();
}

bool Risalnik::AliSeMoramZapreti()
{
    return glfwWindowShouldClose(m_okno);
}

void Risalnik::KonecFrame()
{
    glfwPollEvents();
    glfwSwapBuffers(m_okno);
}

void Risalnik::ZacetekFrame()
{
    glClearColor(odzadje.r, odzadje.g, odzadje.b, odzadje.a);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Risalnik::Konec()
{
    glfwTerminate();
}