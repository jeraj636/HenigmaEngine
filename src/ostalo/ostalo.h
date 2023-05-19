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

namespace io
{
    enum class type
    {
        msg,
        warning,
        error
    };
    void izpis(const char *msg, const type &tip);
}
