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

#define xVel 1.0f / 16.0f
#define yVel 1.0f / 8.0f
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

        // c -= ' ';
        float tocke[20] = {
            1.0f, 1.0f, 0.0f, lokacija[c]->x + xVel, lokacija[c]->y,
            1.0f, -1.0f, 0.0f, lokacija[c]->x + xVel, lokacija[c]->y + yVel,
            -1.0f, -1.0f, 0.0f, lokacija[c]->x, lokacija[c]->y + yVel,
            -1.0f, 1.0f, 0.0f, lokacija[c]->x, lokacija[c]->y};

        /*
                float tocke[20] = {
                    1.0f, 1.0f, 0.0f, lokacija[c]->x + xVel, lokacija[c]->y + yVel,
                    1.0f, -1.0f, 0.0f, lokacija[c]->x, lokacija[c]->y + yVel,
                    -1.0f, -1.0f, 0.0f, lokacija[c]->x + xVel, lokacija[c]->y,
                    -1.0f, 1.0f, 0.0f, lokacija[c]->x, lokacija[c]->y};
        */
        // std::cout << (char)(lokacija.size() - 1) << "    " << j << "   " << i << "\n\n\n\n";
        //  glm::mat4 premik = glm::mat4(1);
        //  premik = glm::translate(premik, glm::vec3(pozicija.x, pozicija.y, pozicija.z));
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(tocke), tocke);

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
    _pisiava = naloziTeksturo(potDoPisave, 1);
    for (int i = 7; i >= 0; i--)
    {
        for (int j = 0; j < 16; j++)
        {
            lokacija.push_back(new mat::vec::Vec2(j * xVel, i * yVel));
            // std::cout << lokacija.size() - 1 << "    " << lokacija.back()->x << "   " << lokacija.back()->y << '\n';
            std::cout << (char)(lokacija.size() - 1) << "    " << j << "   " << i << '\n';
        }
        std::cout << "\n\n";
    }
}
Besedilo::Besedilo()
    : barvaObjekta(0xffffffff), barvaOdzadja(0x00000000)
{
}
