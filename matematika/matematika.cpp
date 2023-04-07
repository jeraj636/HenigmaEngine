#include "matematika.h"
#include "cmath"
mat::vec::Vec3::Vec3(float _x, float _y, float _z)
{
    x = _x;
    y = _y;
    z = _z;
}
mat::vec::Vec2::Vec2(float _x, float _y)
{
    x = _x;
    y = _y;
}

float mat::enacba::linearna::dobiK(mat::vec::Vec2 A, mat::vec::Vec2 B)
{
    float k;
    k = (A.y - B.y) / (A.x - B.x);
    return k;
}
float mat::enacba::linearna::dobiK(mat::vec::Vec2 A, float z)
{
    float k;
    k = A.y - z;
    k /= A.x;
    return k;
}
float mat::enacba::linearna::dobiY(float x, float k, float z)
{
    float y = k * x + z;
    return y;
}
float mat::enacba::linearna::dobiX(float y, float k, float z)
{
    return (y - z) / k;
}
float mat::enacba::linearna::dobiZ(mat::vec::Vec2 A, mat::vec::Vec2 B)
{
    float k = mat::enacba::linearna::dobiK(A, B);
    return mat::enacba::linearna::dobiZ(A, k);
}
float mat::enacba::linearna::dobiZ(mat::vec::Vec2 A, float k)
{
    float z;
    z = A.y - k * A.x;
    return z;
}
mat::vec::Vec2 mat::rot::rotaciskaMatrika(float a, mat::vec::Vec2 T)
{
    mat::vec::Vec2 slikaT(0, 0);

    float x = T.x;
    float y = T.y;

    slikaT.x = T.x * cos(a) - T.y * sin(a);
    slikaT.y = T.x * sin(a) + T.y * cos(a);
    return slikaT;
}

float mat::kot::rad(float a)
{
    float x = 3.14 * a / 180;
    return x;
}
float mat::kot::deg(float a)
{
    float x = 180 * a / 3.14;
    return x;
}
