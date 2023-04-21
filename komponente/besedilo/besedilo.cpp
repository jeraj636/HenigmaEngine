#include "besedilo.h"
#include "../../renderer/renderer.h"
#include "../../objekt/objekt.h"
// #include "../../ostalo/ostalo.h"
#include "../transformacija/transformacija.h"
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../../matematika/matematika.h"
#include <unistd.h>
// #define neki 92.11111f
#define neki 93.9999f
void Besedilo::zanka()
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, _pisiava);
    glBindBuffer(GL_ARRAY_BUFFER, okno->BVBO);

    mat::vec::Vec3 pozicija = objekt->poisciKomponento<Transformacija>()->pozicija;
    mat::vec::Vec3 rotacija = objekt->poisciKomponento<Transformacija>()->rotacija;
    mat::vec::Vec3 velikost = objekt->poisciKomponento<Transformacija>()->velikost;

    for (int i = 0; i < vsebina.length(); i++)
    {
        char c = vsebina[i];

        c -= '!'+1;
        float tocke[20] = {
            1.0f, 1.0f, 0.0f, 1.0f, lokacija[c] + 1.1f/neki,
            1.0f, -1.0f, 0.0f, 1.0f, lokacija[c],
            -1.0f, -1.0f, 0.0f, 0.0f, lokacija[c],
            -1.0f, 1.0f, 0.0f, 0.0f, lokacija[c]+1.1f/neki};

        //! glm::mat4 premik = glm::mat4(1);
        //! premik = glm::translate(premik, glm::vec3(pozicija.x, pozicija.y, pozicija.z));

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
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(tocke), tocke);

        // glUniformMatrix4fv(glGetUniformLocation(okno->shaderProgram, "poz"), 1, GL_FALSE, &premik[0][0]);
        glUniform1i(glGetUniformLocation(okno->shaderProgram, "TID"), 0);
        glUniform4f(glGetUniformLocation(okno->shaderProgram, "odzadje"), barvaOdzadja.r, barvaOdzadja.g, barvaOdzadja.b, barvaOdzadja.a);
        glUniform4f(glGetUniformLocation(okno->shaderProgram, "barva"), barvaObjekta.r, barvaObjekta.g, barvaObjekta.b, barvaObjekta.a);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        pozicija.x += objekt->poisciKomponento<Transformacija>()->velikost.x;
    }
}
void Besedilo::nastavi(Okno *okn, Objekt *obj)
{
    io::izpis("objekt je nastavljen", io::type::msg);
    okno = okn;
    objekt = obj;
}
void Besedilo::naloziPisavo(const char *potDoPisave)
{
    _pisiava = naloziTeksturo(potDoPisave, 0);
    float x = 1.0 / neki;
    for (int i = 0; i <= '~' - '!'; i++)
    {
        // lokacija[i] = lokacija[i - 1] + x;
        lokacija[i] = i * x;
    }
}
Besedilo::Besedilo()
    : barvaObjekta(0xffffffff), barvaOdzadja(0x00000000)
{
}
