#pragma once

namespace mat
{
    namespace vec
    {
        class Vec3;
        class Vec2
        {
        public:
            float x, y;
            Vec2(float _x, float _y);
            Vec2 &operator=(const Vec2 novaVr)
            {
                x = novaVr.x;
                y = novaVr.y;
                return *this;
            }
        };
        class Vec4
        {
        public:
            float x, y, z, w;
            Vec4(float _x, float _y, float _z, float _w)
            {
                x = _x;
                y = _y;
                z = _z;
                w = _w;
            }
            Vec4 &operator=(const Vec4 novaVr)
            {
                x = novaVr.x;
                y = novaVr.y;
                z = novaVr.z;
                w = novaVr.w;
                return *this;
            }
        };
        class Vec3
        {
        public:
            float x, y, z;
            Vec3(float _x, float _y, float _z);
            Vec3 &operator=(const Vec2 novaVr)
            {
                x = novaVr.x;
                y = novaVr.y;
                return *this;
            }
            Vec3 &operator=(const Vec3 novaVr)
            {
                x = novaVr.x;
                y = novaVr.y;
                z = novaVr.z;
                return *this;
            }
            template <typename T>
            Vec3 &
            operator/(const T st)
            {
                x /= st;
                y /= st;
                z /= st;
                return *this;
            }
        };

    }
    namespace enacba
    {
        namespace linearna
        {
            float dobiK(mat::vec::Vec2 A, mat::vec::Vec2 B);
            float dobiK(mat::vec::Vec2 A, float z);
            float dobiZ(mat::vec::Vec2 A, mat::vec::Vec2 B);
            float dobiZ(mat::vec::Vec2 A, float k);
            float dobiY(float x, float k, float z);
            float dobiX(float y, float k, float z);
        }
    }
    namespace rot
    {
        mat::vec::Vec2 rotaciskaMatrika(float a, mat::vec::Vec2 T);
    }
    namespace kot
    {
        float rad(float a);
        float deg(float a);
    }
}