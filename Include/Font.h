#ifndef FONT_H
#define FONT
#include <stdint.h>
#include "Log.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>

class Znak
{
public:
    uint32_t tekID;
    glm::ivec2 velikost;
    glm::ivec2 polozaj;
    uint32_t vnaprej;
    Znak &operator=(Znak &o);
};

class Font
{
public:
    void NaloziFont(std::string potDoFonta, int velikost);
    const Znak &DobiZnak(int koda) const;
    const int DobiVelikost() const;
    Font &operator=(Font &o);
    Znak m_znaki[128];

private:
    int m_velkost;
};
#endif