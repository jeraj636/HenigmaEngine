#include "upodabljalnik.h"
#include "../../renderer/renderer.h"
#include "../../objekt/objekt.h"
#include "../kompinenta.h"
void Upodabljalnik::zanka()
{

    glUseProgram(okno->shaderProgram);
    glBindVertexArray(okno->VAO);
    glUniform4f(glGetUniformLocation(okno->shaderProgram, "barva"), 0, 0, 1, 1);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
Upodabljalnik::Upodabljalnik()
{
}