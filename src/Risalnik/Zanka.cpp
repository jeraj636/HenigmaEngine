#include "../../Include/Risalnik.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

void Risalnik::ZacetekFrame()
{
    glClearColor(odzadje.r, odzadje.g, odzadje.b, odzadje.a);
    glClear(GL_COLOR_BUFFER_BIT);
    double x, y;
    glfwGetCursorPos(m_okno, &x, &y);
    m_pozKazalca.x = x;
    m_pozKazalca.y = y;
    int x1, y1;
    glfwGetWindowSize(m_okno, &x1, &y1);
    m_velOkna.x = x1;
    m_velOkna.y = y1;

    m_orto = glm::ortho(0.0f, (float)m_velOkna.x, (float)m_velOkna.y, 0.0f);
}

void Risalnik::KonecFrame()
{
    glfwPollEvents();
    glfwSwapBuffers(m_okno);
}