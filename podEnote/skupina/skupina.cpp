#include "skupina.h"
#include "../../renderer/renderer.h"
#include "../../ostalo/ostalo.h"
#include "../../objekt/objekt.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

void Skupina::zanka()
{
    glm::mat4 poz;
    poz = glm::mat4(1);
    poz = glm::translate(poz, glm::vec3(pozicija.x, pozicija.y, pozicija.z));
    glUniformMatrix4fv(glGetUniformLocation(okno->shaderProgram, "SPoz"), 1, GL_FALSE, &poz[0][0]);

    glm::mat4 rot;
    rot = glm::mat4(1);
    rot = glm::rotate(rot, glm::radians(rotacija.z), glm::vec3(0.0, 0.0, 1.0));
    glUniformMatrix4fv(glGetUniformLocation(okno->shaderProgram, "SRot"), 1, GL_FALSE, &rot[0][0]);
    for (int i = 0; i < tabObjektov.size(); i++)
    {
        if (tabObjektov[i]->aktivno)
            tabObjektov[i]->zanka();
    }
    for (int i = 0; i < tabSkupn.size(); i++)
        if (tabSkupn[i]->aktivno)
            tabSkupn[i]->zanka();
}
Objekt *Skupina::dodajObjekt(std::string ime)
{
    tabObjektov.push_back(new Objekt(okno, ime));
    return tabObjektov.back();
}
Skupina::Skupina(Okno *okn, std::string _ime)
    : pozicija(0, 0, 0), rotacija(0, 0, 0)
{
    okno = okn;
    ime = _ime;
}
Objekt *Skupina::poisciObjekt(std::string ime)
{
    for (int i = 0; i < tabObjektov.size(); i++)
    {
        if (tabObjektov[i]->ime == ime)
            return tabObjektov[i];
    }
    return nullptr;
}

Skupina::~Skupina()
{
    for (int i = 0; i < tabSkupn.size(); i++)
        delete tabSkupn[i];
    for (int i = 0; i < tabObjektov.size(); i++)
        delete tabObjektov[i];
}