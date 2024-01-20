#include <cmath>

#include "../include/barva.h"

Barva::Barva(uint32_t hex_code)
{
    m_a = hex_code & 0x000000ff;
    hex_code >>= 8;
    m_b = hex_code & 0x0000ff;
    hex_code >>= 8;
    m_g = hex_code & 0x00ff;
    hex_code >>= 8;
    m_r = hex_code & 0xff;

    m_r /= 0xff;
    m_g /= 0xff;
    m_b /= 0xff;
    m_a /= 0xff;
}

Barva &Barva::operator=(uint32_t hex_code)
{
    m_a = hex_code & 0x000000ff;
    hex_code >>= 8;
    m_b = hex_code & 0x0000ff;
    hex_code >>= 8;
    m_g = hex_code & 0x00ff;
    hex_code >>= 8;
    m_r = hex_code & 0xff;

    m_r /= 0xff;
    m_g /= 0xff;
    m_b /= 0xff;
    m_a /= 0xff;
    return *this;
}

const float Barva::get_r() const
{
    return m_r;
}

const float Barva::get_g() const
{
    return m_g;
}

const float Barva::get_b() const
{
    return m_b;
}

const float Barva::get_a() const
{
    return m_a;
}

void Barva::set_r(float hex_code)
{
    m_r = hex_code / 0xff;
}

void Barva::set_g(float hex_code)
{
    m_g = hex_code / 0xff;
}

void Barva::set_b(float hex_code)
{
    m_b = hex_code / 0xff;
}

void Barva::set_a(float hex_code)
{
    m_a = hex_code / 0xff;
}