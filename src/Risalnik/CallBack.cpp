#include "../../Include/Risalnik.h"
#include "../../Include/Log.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

void Risalnik::VelikostOknaCallBack(GLFWwindow *okno, int dolzina, int visina)
{
    glViewport(0, 0, dolzina, visina);
}

void Risalnik::GumbCallBack(GLFWwindow *okno, int key, int scanCode, int akcija, int mods)
{
    if (key == GLFW_KEY_ESCAPE && akcija == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(m_okno, 1);
    }
}

void Risalnik::NaloziCallBack()
{
    glfwSetFramebufferSizeCallback(m_okno, VelikostOknaCallBack);
    glfwSetKeyCallback(m_okno, GumbCallBack);
}