#include "Render.h"

#include <ft2build.h>
#include FT_FREETYPE_H

Font::Font(const std::string &pot, int velikost)
{
    NaloziFont(pot, velikost);
}
Font::Font() = default;
void Font::NaloziFont(const std::string &pot, int velikost)
{
    FT_Library ft;

    if (FT_Init_FreeType(&ft))
    {
        spl::io::err("NI NALOZILO TTF");
    }
    spl::io::msg("DELUJE TTF");

    FT_Face face;

    if (FT_New_Face(ft, pot.c_str(), 0, &face))
    {
        spl::io::err("NI NALOZILO GLAVE");
    }
    spl::io::msg("DELUJE OBRAZ");

    FT_Set_Pixel_Sizes(face, 0, 25);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    for (int i = 0; i < 128; i++)
    {
        if (FT_Load_Char(face, i, FT_LOAD_RENDER))
        {
            spl::io::war("NI NALOZILO ZNAKA");
            continue;
        }
        // spl::io::msg("ZNAK NALOZEN");
        uint32_t tekstura;
        glGenTextures(1, &tekstura);
        glBindTexture(GL_TEXTURE_2D, tekstura);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, face->glyph->bitmap.width, face->glyph->bitmap.rows, 0, GL_RED, GL_UNSIGNED_BYTE, face->glyph->bitmap.buffer);

        znaki[i].TeksturaID = tekstura;
        znaki[i].velikost = spl::vec2(face->glyph->bitmap.width, face->glyph->bitmap.rows);
        znaki[i].ofset = spl::vec2(face->glyph->bitmap_left, face->glyph->bitmap_top);
        znaki[i].odmik = face->glyph->advance.x;
    }

    FT_Done_Face(face);
    FT_Done_FreeType(ft);
}