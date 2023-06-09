#include "ostalo.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
int vDec(char c)
{
    switch (c)
    {
    case 'a':
        return 10;
    case 'b':
        return 11;
    case 'c':
        return 12;
    case 'd':
        return 13;
    case 'e':
        return 14;
    case 'f':
        return 15;
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
        return c - 48;
    }
    return 0;
}
Barva::Barva(std::string hexCode)
{
    a = vDec(hexCode[hexCode.size() - 1]) + vDec(hexCode[hexCode.size() - 2]) * 16;
    b = vDec(hexCode[hexCode.size() - 3]) + vDec(hexCode[hexCode.size() - 4]) * 16;
    g = vDec(hexCode[hexCode.size() - 5]) + vDec(hexCode[hexCode.size() - 6]) * 16;
    r = vDec(hexCode[hexCode.size() - 7]) + vDec(hexCode[hexCode.size() - 8]) * 16;
    a /= 0xff;
    r /= 0xff;
    g /= 0xff;
    b /= 0xff;
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
Barva::Barva()
{
    a = 0xff;
    b = 0xff;
    g = 0xff;
    r = 0xff;
}
#define _DEBUG
#ifdef _DEBUG
void spl::io::err(const std::string &sporocilo)
{
    fmt::print(fg(fmt::color::red), "ERROR: {}\nKONEC PROGRAMA!\n", sporocilo.c_str());
    exit(-1);
}
void spl::io::war(const std::string &sporocilo)
{
    fmt::print(fg(fmt::color::violet), "WARNING: ");
    fmt::print("{}\n", sporocilo.c_str());
}
void spl::io::msg(const std::string &sporocilo)
{
    fmt::print(fg(fmt::color::green), "MSG: ");
    fmt::print("{}\n", sporocilo.c_str());
}

#else

void spl::io::err(const std::string &sporocilo)
{
}
void spl::io::war(const std::string &sporocilo)
{
}
void spl::io::msg(const std::string &sporocilo)
{
}
#endif
