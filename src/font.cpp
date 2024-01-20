#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <fstream>

#include "../include/font.h"
#include "../include/log.h"
#define STB_TRUETYPE_IMPLEMENTATION
#include "../lib/stb/stb_true_type.h"

Font::Font(const std::string &pot, uint32_t velikost)
{
    std::ifstream datoteka(pot, std::ios::binary);

    if (!datoteka.is_open())
        log::err("NI FONTA");

    datoteka.seekg(0, std::ios::end);
    int vel = datoteka.tellg();
    datoteka.seekg(0, std::ios::beg);

    unsigned char *ttf_data = new unsigned char[vel];

    datoteka.read((char *)ttf_data, vel);
    if (datoteka.fail())
        log::err("NAPAKA V DATOTEKI FONTA");

    unsigned char *bitmap = new unsigned char[512 * 512];
    int res = stbtt_BakeFontBitmap(ttf_data, 0, velikost, bitmap, 512, 512, '\0', 128, char_data);

    glGenTextures(1, &tekstura);
    glBindTexture(GL_TEXTURE_2D, tekstura);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, 512, 512, 0, GL_RED, GL_UNSIGNED_BYTE, bitmap);

    delete[] ttf_data;
    delete[] bitmap;
}