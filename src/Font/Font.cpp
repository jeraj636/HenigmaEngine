#include "../../Include/Font.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include <ft2build.h>
#include FT_FREETYPE_H

const int Font::DobiVelikost() const
{
    return m_velkost;
}
const Znak &Font::DobiZnak(int koda) const
{
    return m_znaki[koda];
}
void Font::NaloziFont(std::string potDoFonta, int velikost)
{
    m_velkost = velikost;

    FT_Library ft;
    if (FT_Init_FreeType(&ft))
        io::err("NI INICIALIZIRANE KNJIZNICE ZA PISAVE");
    FT_Face obraz;
    if (FT_New_Face(ft, potDoFonta.c_str(), 0, &obraz))
        io::err("NI OBRAZA");

    FT_Set_Pixel_Sizes(obraz, 0, 48);

    for (int i = 0; i < 128; i++)
    {
        if (FT_Load_Char(obraz, (char)i, FT_LOAD_RENDER))
        {
            continue;
        }

        uint32_t tek;
        glGenTextures(1, &tek);
        glBindTexture(GL_TEXTURE_2D, tek);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, obraz->glyph->bitmap.width, obraz->glyph->bitmap.rows, 0, GL_RED, GL_UNSIGNED_BYTE, obraz->glyph->bitmap.buffer);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        m_znaki[i].tekID = tek;
        // std::cout << tek << std::endl;
        m_znaki[i].velikost = glm::ivec2(obraz->glyph->bitmap.width, obraz->glyph->bitmap.rows);
        m_znaki[i].polozaj = glm::ivec2(obraz->glyph->bitmap_left, obraz->glyph->bitmap_top);
        m_znaki[i].tekID = obraz->glyph->advance.x;
    }
    FT_Done_Face(obraz);
    FT_Done_FreeType(ft);
}