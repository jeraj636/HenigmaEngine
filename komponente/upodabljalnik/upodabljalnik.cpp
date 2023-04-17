#include "upodabljalnik.h"

#include "../../renderer/renderer.h"
#include "../../objekt/objekt.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

void Upodabljalnik::zanka()
{

    glUseProgram(okno->shaderProgram);
    glBindVertexArray(okno->VAO);
    glActiveTexture(GL_TEXTURE0);

    glBindTexture(GL_TEXTURE_2D, 1);

    mat::vec::Vec3 pozicija = objekt->poisciKomponento<Transformacija>()->pozicija;
    mat::vec::Vec3 rotacija = objekt->poisciKomponento<Transformacija>()->rotacija;
    mat::vec::Vec3 velikost = objekt->poisciKomponento<Transformacija>()->velikost;

    glm::mat4 poz = glm::mat4(1);
    glm::mat4 rot = glm::mat4(1);
    glm::mat4 vel = glm::mat4(1);

    poz = glm::translate(poz, glm::vec3(pozicija.x, pozicija.y, pozicija.z));
    // vel = glm::scale(vel, glm::vec3(velikost.x, velikost.y, velikost.z));
    vel = glm::scale(vel, glm::vec3(velikost.x / 2, velikost.y / 2, velikost.z / 2));
    rot = glm::rotate(rot, glm::radians(rotacija.z), glm::vec3(0, 0, 1));
    glUniformMatrix4fv(glGetUniformLocation(okno->shaderProgram, "poz"), 1, GL_FALSE, &poz[0][0]);
    glUniformMatrix4fv(glGetUniformLocation(okno->shaderProgram, "rot"), 1, GL_FALSE, &rot[0][0]);
    glUniformMatrix4fv(glGetUniformLocation(okno->shaderProgram, "vel"), 1, GL_FALSE, &vel[0][0]);
    glUniformMatrix4fv(glGetUniformLocation(okno->shaderProgram, "pravopis"), 1, GL_FALSE, &okno->pravopis[0][0]);
    glUniform1i(glGetUniformLocation(okno->shaderProgram, "TID"), 0);
    glUniform4f(glGetUniformLocation(okno->shaderProgram, "barva"), barvaOdzadja.r, barvaOdzadja.g, barvaOdzadja.b, barvaOdzadja.a);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    io::izpis("tukaj sem    ", io::type::msg);

    glBindTexture(GL_TEXTURE_2D, tekstura);

    glUniform1i(glGetUniformLocation(okno->shaderProgram, "TID"), 0);
    glUniform4f(glGetUniformLocation(okno->shaderProgram, "barva"), barvaObjekta.r, barvaObjekta.g, barvaObjekta.b, barvaObjekta.a);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
Upodabljalnik::Upodabljalnik()
    : barvaObjekta(0xffffffff), barvaOdzadja(0xffffff00)
{
    tekstura = naloziTeksturo("tt.png", 1);
}