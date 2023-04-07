
#include "transformacija.h"

#include "../../renderer/renderer.h"
#include "../../objekt/objekt.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

void Transformacija::zanka()
{
    glm::mat4 poz = glm::mat4(1);
    glm::mat4 rot = glm::mat4(1);
    glm::mat4 vel = glm::mat4(1);

    poz = glm::translate(poz, glm::vec3(pozicija.x, pozicija.y, pozicija.z));
    vel = glm::scale(vel, glm::vec3(velikost.x, velikost.y, velikost.z));
    rot = glm::rotate(rot, glm::radians(rotacija.z), glm::vec3(0, 0, 1));

    glUniformMatrix4fv(glGetUniformLocation(okno->shaderProgram, "poz"), 1, GL_FALSE, &poz[0][0]);
    glUniformMatrix4fv(glGetUniformLocation(okno->shaderProgram, "rot"), 1, GL_FALSE, &rot[0][0]);
    glUniformMatrix4fv(glGetUniformLocation(okno->shaderProgram, "vel"), 1, GL_FALSE, &vel[0][0]);
    glUniformMatrix4fv(glGetUniformLocation(okno->shaderProgram, "pravopis"), 1, GL_FALSE, &okno->pravopis[0][0]);
}

Transformacija::Transformacija()
    : pozicija(0.0, 0.0, 0.0), velikost(1.0, 1.0, 1.0), rotacija(0.0, 0.0, 0.0)
{
}
