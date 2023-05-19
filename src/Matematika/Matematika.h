#ifndef MATEMATIKA_H
#define MATEMATIKA_H
namespace spl
{
    class vec3
    {
    public:
        vec3();
        vec3(float t_x, float t_y, float t_z);
        vec3(vec3 &v);
        vec3 operator=(vec3 o);
        vec3 &operator+(vec3 o);
        //  vec3 operator-(vec3 o);
        float x, y, z;
    };
}
#endif