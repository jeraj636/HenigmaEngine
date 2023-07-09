#include "../../Include/Risalnik.h"
#include "../../Include/Log.h"
#include "../../Include/Font.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

void Risalnik::Init(const char *naslov)
{

    OdpriOkno(naslov);

    NaloziCallBack();

    NarediShaderje();
    NaloziBufferje();

    NarediShaderjeB();
    NaloziBufferjeB();

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glfwSwapInterval(0);
    // glActiveTexture(GL_TEXTURE0);

    // glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
}
void Risalnik::OdpriOkno(const char *naslov)
{
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_okno = glfwCreateWindow(800, 600, naslov, NULL, NULL);
    if (m_okno == nullptr)
    {
        glfwTerminate();
        io::err("NI OKNA");
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
}
bool Risalnik::AliSeMoramZapreti()
{
    return glfwWindowShouldClose(m_okno);
}
