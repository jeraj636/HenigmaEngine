#include "Matematika.h"
#include <cmath>
using namespace spl;
vec3::vec3()
{
    x = 0;
    y = 0;
    z = 0;
}
vec3::vec3(float t_x, float t_y, float t_z)
{
    x = t_x;
    y = t_y;
    z = t_z;
}
vec3::vec3(vec3 &v)
{
    x = v.x;
    y = v.y;
    z = v.z;
}
vec3 &operator=(vec3 o)
{
    vec3 t(o);
    return t;
}
vec3 &operator+(vec3 o)
{
    vec3 razultat(this->x + o.x, this->y + o.y, this->z + o.z);
    return rezultat;
}