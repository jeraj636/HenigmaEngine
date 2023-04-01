#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../ostalo/ostalo.h"
#include "../podEnote/scena/scena.h"
#include <vector>
class Okno
{
public:
    uint VAO, shaderProgram;
    GLFWwindow *okno;
    Barva barvaOdzadja;
    std::vector<Scena *> tabScen;
    Okno(int width, int height, const char *naslov);

    void zanka();
    Scena *dodajSceno();

private:
    static void posodobiVelikost(GLFWwindow *okko, int width, int height)
    {
        glViewport(0, 0, width, height);
    }
};