#ifndef MATEMATIKA_H
#define MATEMATIKA_H
class vec3
{
public:
    vec3(float t_x, float t_y, float t_z);
    vec3(vec3 &v);
    // vec3();
    vec3() = default;
    vec3 &operator=(const vec3 &o);
    vec3 &operator=(const float f);
    vec3 operator+(const vec3 &o);
    vec3 &operator+=(const vec3 &o);
    vec3 operator-(const vec3 &o);
    vec3 &operator-=(const vec3 &o);
    vec3 operator+(const float v);
    vec3 &operator+=(const float v);
    vec3 operator-(const float v);
    vec3 &operator-=(const float v);
    float x, y, z;
};

class vec2
{
public:
    vec2(float t_x, float t_y);
    vec2(vec2 &v);
    // vec2();
    vec2() = default;
    vec2 &operator=(const vec2 &o);
    vec2 &operator=(const float f);
    vec2 operator+(const vec2 &o);
    vec2 &operator+=(const vec3 &o);
    vec2 operator-(const vec2 &o);
    vec2 &operator-=(const vec2 &o);
    vec2 operator+(const float v);
    vec2 &operator+=(const float v);
    vec2 operator-(const float v);
    vec2 &operator-=(const float v);

    float x, y;
};
#endif