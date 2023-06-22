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
};

class Font
{
public:
    void NaloziFont(std::string potDoFonta, int velikost);
    const Znak &DobiZnak(int koda) const;
    const int DobiVelikost() const;

private:
    Znak m_znaki[128];
    int m_velkost;
};
#endif