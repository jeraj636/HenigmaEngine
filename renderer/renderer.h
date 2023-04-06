#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include "../ostalo/ostalo.h"
class Scena;
class Okno
{
public:
    uint VAO, shaderProgram;
    GLFWwindow *okno;
    Barva barvaOdzadja;
    Okno(int width, int height, const char *naslov);
    glm::mat4 pravopis;
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