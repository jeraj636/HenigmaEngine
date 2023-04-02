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
    Okno(int width, int height, const char *naslov);

    void zanka();
    Scena *dodajSceno();
    ~Okno();

private:
    std::vector<Scena *> tabScen;
    static void posodobiVelikost(GLFWwindow *okko, int width, int height)
    {
        glViewport(0, 0, width, height);
    }
};