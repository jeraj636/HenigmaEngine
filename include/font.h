#ifndef FONT_H
#define FONT_H

#include <stdint.h>
#include <matematika/matematika.h>
#include <string>
#include <stb/stb_true_type.h>

class Font
{
public:
    Font(const std::string &pot);
    Font() = default;
    Font(const Font &f);
    Font &operator=(const Font &f);
    stbtt_bakedchar char_data[128];
    uint32_t tekstura;

private:
};
#endif