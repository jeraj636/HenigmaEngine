#ifndef BARVA_H
#define BARVA_H
#include <cstdint>
class Barva
{
public:
    Barva() = default;
    Barva(uint32_t hex_code);
    Barva &operator=(uint32_t hex_code);

    const float get_r() const;
    const float get_g() const;
    const float get_b() const;
    const float get_a() const;

    void set_r(float hex_code);
    void set_g(float hex_code);
    void set_b(float hex_code);
    void set_a(float hex_code);

private:
    float m_r;
    float m_g;
    float m_b;
    float m_a;
};

#endif