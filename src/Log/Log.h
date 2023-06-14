#ifndef LOG_H
#define LOG_H

#include <fmt/core.h>
#include <fmt/color.h>
#include <string>

class io
{
public:
#ifdef DEBUG
    static void err(const std::string &sporocilo)
    {
        fmt::print(fg(fmt::color::red), "ERR: ");
        fmt::print("{}\n", sporocilo.c_str());
        fmt::print(fg(fmt::color::red), "KONEC PROGRAMA!\n");
    }
    static void msg(const std::string &sporocilo)
    {
        fmt::print(fg(fmt::color::green), "MSG: ");
        fmt::print("{}\n", sporocilo.c_str());
    }
    static void war(const std::string &sporocilo)
    {
        fmt::print(fg(fmt::color::violet), "WAR: ");
        fmt::print("{}\n", sporocilo.c_str());
    }
#endif

#ifndef DEBUG
    static void msg(const std::string &sporocilo)
    {
    }
    static void war(const std::string &sporocilo)
    {
    }
    static void err(const std::string &sporocilo)
    {
    }
#endif
};
#endif