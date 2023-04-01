#include "objekt.h"
#include "../renderer/renderer.h"
Objekt::Objekt(Okno *okn)
{
    okno = okn;
}
void Objekt::zanka()
{
    glUseProgram(okno->shaderProgram);
    glBindVertexArray(okno->VAO);
    glUniform4f(glGetUniformLocation(okno->shaderProgram, "barva"), 0, 1, 1, 1);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}