#pragma once
#include <fmt/core.h>
#include <fmt/color.h>
#include <string>
#include <cstring>
class Barva
{
public:
    float a, b, g, r;
    Barva(int hexCode);
};




namespace spl
{
    class io
    {
    public:
        static void err(const std::string& sporocilo);
        static void war(const std::string& sporocilo);
        static void msg(const std::string& sporocilo);
    private:
    };
}
