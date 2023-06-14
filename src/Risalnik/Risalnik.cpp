#include "Risalnik.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "../Log/Log.h"

void Risalnik::Init(const char *naslov)
{
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_okno = glfwCreateWindow(800, 600, naslov, NULL, NULL);

    if (m_okno == nullptr)
    {
        glfwTerminate();
        io::err("NI OKNOA");
    }
    io::msg("OKNO DELUJE");

    glfwMakeContextCurrent(m_okno);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        glfwTerminate();
        io::err("NI GLADA");
    }
    io::msg("GLAD DELUJE");

    glViewport(0, 0, 800, 600);

    // glfwSetFramebufferSizeCallback(m_okno, VelikostOknaCallBack);
}
void Risalnik::Zanka()
{
    glfwSwapBuffers(m_okno);
    glfwPollEvents();
}
bool Risalnik::AliSeMoramZapreti()
{
    // return glfwWindowShouldClose(m_okno);
    return 1;
}