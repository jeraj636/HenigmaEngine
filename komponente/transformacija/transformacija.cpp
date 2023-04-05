
#include "transformacija.h"
#include "../../renderer/renderer.h"
#include "../../objekt/objekt.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

void Transformacija::zanka()
{
    glm::mat4 matrika = glm::mat4(1);
    matrika *= glm::translate(matrika, glm::vec3(pozicija.x, pozicija.y, pozicija.z));
    matrika *= glm::scale(matrika, glm::vec3(velikost.x, velikost.y, velikost.z));
    matrika *= glm::rotate(matrika, glm::radians(rotacija.z), glm::vec3(0, 0, 1));
    glUniformMatrix4fv(glGetUniformLocation(okno->shaderProgram, "pozicija"), 1, GL_FALSE, &matrika[0][0]);
}
Transformacija::Transformacija()
    : pozicija(0.0, 0.0, 0.0), velikost(1.0, 1.0, 1.0), rotacija(0.0, 0.0, 0.0)
{
}
