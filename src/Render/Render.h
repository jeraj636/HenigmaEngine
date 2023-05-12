#pragma once
#include <cstdint>
// #include "../glad/include/glad/glad.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include "../ostalo/ostalo.h"
class Render
{
public:
    Render(std::string ime);
    void Init(std::string ime);
    // void Narisi();
    // void DodajSceno();
    // void AktivirajSceno();
    void Zanka();
    bool AliSeMoramZapreti();
    void OkvirZac();
    void OkvirKon();
    Barva Odzadje;

private:
    GLFWwindow *m_okno;
    static void PosodobiVelOkna(GLFWwindow *okno, int dolzina, int visina)
    {
        glViewport(0, 0, dolzina, visina);
    }
    void DobiVhod()
    {
        if (glfwGetKey(m_okno, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(m_okno, GLFW_TRUE);
    }
};