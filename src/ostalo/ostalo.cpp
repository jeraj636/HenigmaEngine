#include "ostalo.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

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
