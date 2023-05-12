#include "Render.h"
#include "../ostalo/ostalo.h"
Render::Render(std::string ime)
    : Odzadje(0xffffffff)
{
    // Init(ime);
}
void Render::Init(std::string ime)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_okno = glfwCreateWindow(800, 600, ime.c_str(), NULL, NULL);

    if (m_okno == NULL)
    {
        io::izpis("NI USTVARILO OKNA", io::type::error);
    }
    glfwMakeContextCurrent(m_okno);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        io::izpis("NI USTVARILO GLAD-a", io::type::error);
    }

    glfwSetFramebufferSizeCallback(m_okno, PosodobiVelOkna);
}
bool Render::AliSeMoramZapreti()
{
    if (glfwWindowShouldClose(m_okno))
        return true;
    return false;
}
void Render::OkvirKon()
{
    glfwSwapBuffers(m_okno);
    glfwPollEvents();
}
void Render::OkvirZac()
{
    DobiVhod();
}
void Render::Zanka()
{
    glClearColor(Odzadje.r, Odzadje.g, Odzadje.b, Odzadje.a);
    glClear(GL_COLOR_BUFFER_BIT);
}
