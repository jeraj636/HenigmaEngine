#include "upodabljalnik.h"
#include "../../renderer/renderer.h"
#include "../../objekt/objekt.h"
#include "../kompinenta.h"
void Upodabljalnik::zanka()
{

    glUseProgram(okno->shaderProgram);
    glBindVertexArray(okno->VAO);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, tekstura);

    glUniform1i(glGetUniformLocation(okno->shaderProgram, "TID"), 0);
    glUniform4f(glGetUniformLocation(okno->shaderProgram, "barva"), barvaObjekta.r, barvaObjekta.g, barvaObjekta.b, barvaObjekta.a);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
Upodabljalnik::Upodabljalnik()
    : barvaObjekta(0xffffffff)
{
    tekstura = naloziTeksturo("tt.png");
}