#include "gumb.h"
#include "../transformacija/transformacija.h"
#include "../../renderer/renderer.h"
#include "../../objekt/objekt.h"
#include <iostream>
#include <limits>

void Gumb::zanka()
{
    double x, y;
    DobiPozicijoKazalca(x, y);
    mat::vec::Vec2 A(0, 0);
    mat::vec::Vec2 B(0, 0);
    mat::vec::Vec2 C(0, 0);
    mat::vec::Vec2 D(0, 0);

    mat::vec::Vec2 kazalec((float)x, (float)y);

    nastaviTocke(A, B, C, D);

    float kAD = mat::enacba::linearna::dobiK(A, D);
    if (std::isinf(kAD))
    {
        kAD = 100000.0;
    }
    float zAD = mat::enacba::linearna::dobiZ(A, kAD);
    float zBC = mat::enacba::linearna::dobiZ(B, kAD);

    float kDC = mat::enacba::linearna::dobiK(D, C);
    if (std::isinf(kDC))
    {
        kDC = 100000.0;
    }
    float zDC = mat::enacba::linearna::dobiZ(D, kDC);
    float zAB = mat::enacba::linearna::dobiZ(A, kDC);
    if (aliSemPritisnjen(kazalec, zAD, zBC, zDC, zAB, kDC, kAD) && glfwGetMouseButton(okno->okno, GLFW_MOUSE_BUTTON_LEFT))
    {
        io::izpis("ok", io::type::msg);
    }
}
bool Gumb::aliSemPritisnjen(mat::vec::Vec2 kazalec, float zAD, float zBC, float zDC, float zAB, float kDC, float kAD)
{
    if (zAD > zBC)
    {
        int t = zBC;
        zBC = zAD;
        zAD = t;
    }
    if (zDC > zAB)
    {
        int t = zAB;
        zAB = zDC;
        zDC = t;
    }
    if (zAD <= mat::enacba::linearna::dobiZ(kazalec, kAD) && mat::enacba::linearna::dobiZ(kazalec, kAD) <= zBC)
    {
        if (zDC <= mat::enacba::linearna::dobiZ(kazalec, kDC) && mat::enacba::linearna::dobiZ(kazalec, kDC) <= zAB)
            return 1;
    }
    return 0;
}
void Gumb::nastavi(Okno *okn, Objekt *obj)
{
    io::izpis("objekt je nastavljen", io::type::msg);
    okno = okn;
    objekt = obj;
    if (objekt != nullptr)
        tr = objekt->poisciKomponento<Transformacija>();
    else
        io::izpis("Gumb ni transformacije", io::type::error);
}
void Gumb::DobiPozicijoKazalca(double &x, double &y)
{
    glfwGetCursorPos(okno->okno, &x, &y);
    std::cout.flush();
    int dolzina, visina;
    glfwGetWindowSize(okno->okno, &dolzina, &visina);
    dolzina /= 2;
    visina /= 2;
    x -= dolzina;
    y -= visina;
}
void Gumb::nastaviTocke(mat::vec::Vec2 &A, mat::vec::Vec2 &B, mat::vec::Vec2 &C, mat::vec::Vec2 &D)
{
    A.x = tr->velikost.x * -1;
    A.y = tr->velikost.y * -1;

    B.x = tr->velikost.x;
    B.y = tr->velikost.y * -1;

    C.x = tr->velikost.x;
    C.y = tr->velikost.y;

    D.x = tr->velikost.x * -1;
    D.y = tr->velikost.y;

    A.x += tr->pozicija.x;
    A.y += tr->pozicija.y;

    B.x += tr->pozicija.x;
    B.y += tr->pozicija.y;

    C.x += tr->pozicija.x;
    C.y += tr->pozicija.y;

    D.x += tr->pozicija.x;
    D.y += tr->pozicija.y;

    A = mat::rot::rotaciskaMatrika(mat::kot::rad(tr->rotacija.z), A);
    B = mat::rot::rotaciskaMatrika(mat::kot::rad(tr->rotacija.z), B);
    C = mat::rot::rotaciskaMatrika(mat::kot::rad(tr->rotacija.z), C);
    D = mat::rot::rotaciskaMatrika(mat::kot::rad(tr->rotacija.z), D);
}