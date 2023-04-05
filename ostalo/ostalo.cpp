#include "ostalo.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
Vec3::Vec3(float _x, float _y, float _z)
{
    x = _x;
    y = _y;
    z = _z;
}
uint naloziTeksturo(const char *potDoSlike)
{
    char slika[40];
    strcpy(slika, "../slike/");
    strcat(slika, potDoSlike);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    uint tekstura;
    glGenTextures(1, &tekstura);
    glBindTexture(GL_TEXTURE_2D, tekstura);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    stbi_set_flip_vertically_on_load(1);
    int width, height, chanels;
    unsigned char *data = stbi_load(slika, &width, &height, &chanels, STBI_rgb_alpha);

    if (data != NULL)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    }
    else
        io::izpis("NI SLIKE", io::type::msg);
    return tekstura;
}
Barva::Barva(int hexCode)
{
    a = hexCode & 0x000000ff;
    hexCode >>= 8;
    b = hexCode & 0x0000ff;
    hexCode >>= 8;
    g = hexCode & 0x00ff;
    hexCode >>= 8;
    r = hexCode & 0xff;
    a /= 0xff;
    r /= 0xff;
    g /= 0xff;
    b /= 0xff;
}
namespace io
{
    void izpis(const char *msg, const type &tip)
    {
        static int w = 0;
        static int s = 0;
        if (tip == type::error)
        {
            fmt::print(fg(fmt::color::red), "ERROR: {}\nKONEC PROGRAMA!\n", msg);
            exit(-1);
        }
        else if (tip == type::msg)
        {
            fmt::print(fg(fmt::color::green), "{}: MSG: ", s++);
            fmt::print("{}\n", msg);
        }
        else if (tip == type::warning)
        {
            fmt::print(fg(fmt::color::green), "{}: WARNING: ", w++);
            fmt::print("{}\n", msg);
        }
    }
}