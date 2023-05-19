#ifndef MATEMATIKA_H
#define MATEMATIKA_H
namespace spl
{
    class vec3
    {
    public:
        vec3(float t_x, float t_y, float t_z)
        {
            x = t_x;
            y = t_y;
            z = t_z;
        }
        vec3(vec3 &v)
        {
            x = v.x;
            y = v.y;
            z = v.z;
        }
        vec3()
        {
            vec3(0, 0, 0);
        }
        vec3 &operator=(const vec3 &o)
        {
            this->x = o.x;
            this->y = o.y;
            this->z = o.z;
            return *this;
        }
        vec3 &operator=(const float f)
        {
            this->x = f;
            this->y = f;
            this->z = f;
            return *this;
        }
        vec3 operator+(const vec3 &o)
        {
            vec3 rez;
            rez.x = x + o.x;
            rez.y = y + o.y;
            rez.z = z + o.z;
            return rez;
        }
        vec3 &operator+=(const vec3 &o)
        {
            this->x += o.x;
            this->y += o.y;
            this->z += o.z;
            return *this;
        }
        vec3 operator-(const vec3 &o)
        {
            vec3 rez;
            rez.x = x - o.x;
            rez.y = y - o.y;
            rez.z = z - o.z;
            return rez;
        }
        vec3 &operator-=(const vec3 &o)
        {
            this->x -= o.x;
            this->y -= o.y;
            this->z -= o.z;
            return *this;
        }

        vec3 operator+(const float v)
        {
            vec3 rez(x + v, y + v, z + v);
            return rez;
        }
        vec3 &operator+=(const float v)
        {
            x += v;
            y += v;
            z += v;
            return *this;
        }
        vec3 operator-(const float v)
        {
            vec3 rez(x - v, y - v, z - v);
            return rez;
        }
        vec3 &operator-=(const float v)
        {
            x -= v;
            y -= v;
            z -= v;
            return *this;
        }

        float x, y, z;
    };
}
#endif
