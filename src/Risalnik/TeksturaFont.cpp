#include "../../Include/Risalnik.h"
#include "../../Include/Log.h"
#include "../../Include/Font.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define STB_IMAGE_IMPLEMENTATION
#include "STBImage.h"

uint32_t Risalnik::NaloziTeksturo(std::string potDoSlike)
{
    std::string pot = Risalnik::sredstvaPath + "/" + potDoSlike;
    uint32_t tekstura;
    glGenTextures(1, &tekstura);
    glBindTexture(GL_TEXTURE_2D, tekstura);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    int dolzina, visina, kanali;
    stbi_set_flip_vertically_on_load(1);

    unsigned char *data = stbi_load(pot.c_str(), &dolzina, &visina, &kanali, 4);
    if (!data)
    {
        io::war(pot.c_str());
        io::err("NI SLIKE");
    }
    else
    {
        io::msg("SLIKA DELUJE");
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, dolzina, visina, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    }
    stbi_image_free(data);
    return tekstura;
}
Font Risalnik::NaloziFont(std::string potDoFonta, int velikost)
{
    std::string dejPot = sredstvaPath + '/' + potDoFonta;
    io::war(dejPot.c_str());
    Font t;
    t.NaloziFont(dejPot, velikost);
    return t;
}
