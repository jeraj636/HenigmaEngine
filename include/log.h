#ifndef LOG_H
#define LOG_H

#include <fmt/core.h>
#include <fmt/color.h>
#include <string>
#define DEBUG
class log
{
public:
#ifdef DEBUG
    static void err(const std::string &sporocilo)
    {
        fmt::print(fg(fmt::color::red), "ERR: ");
        fmt::print("{}\n", sporocilo.c_str());
        fmt::print(fg(fmt::color::red), "KONEC PROGRAMA!");
        exit(-1);
    }
    static void war(const std::string &sporocilo)
    {
        fmt::print(fg(fmt::color::orange), "WAR: ");
        fmt::print("{}\n", sporocilo.c_str());
    }
    static void msg(const std::string &sporocilo)
    {
        fmt::print(fg(fmt::color::green), "MSG: ");
        fmt::print("{}\n", sporocilo.c_str());
    }
#endif
#ifndef DEBUG
    static void err(const std::string &sporocilo)
    {
    }
    static void war(const std::string &sporocilo)
    {
    }
    static void msg(const std::string &sporocilo)
    {
    }
#endif
};
#endif