#include "upodabljalnik.h"
#include "../../renderer/renderer.h"
#include "../../objekt/objekt.h"
#include "../kompinenta.h"
void Upodabljalnik::zanka()
{

    glUseProgram(okno->shaderProgram);
    glBindVertexArray(okno->VAO);
    glUniform4f(glGetUniformLocation(okno->shaderProgram, "barva"), barvaObjekta.r, barvaObjekta.g, barvaObjekta.b, barvaObjekta.a);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
Upodabljalnik::Upodabljalnik()
    : barvaObjekta(0xffffffff)
{
}