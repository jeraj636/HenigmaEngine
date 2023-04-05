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

uint naloziTeksturo(const char *potDoSlike);
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
class Vec3
{
public:
    float x, y, z;
    Vec3(float _x, float _y, float _z);
};