#include "gumb.h"
#include "../transformacija/transformacija.h"
#include "../../renderer/renderer.h"
#include "../../objekt/objekt.h"
#include <iostream>
void Gumb::zanka()
{
    double x, y;
    DobiPozicijoKazalca(x, y);
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
    // double x, y;
    glfwGetCursorPos(okno->okno, &x, &y);
    std::cout.flush();
    int dolzina, visina;
    glfwGetWindowSize(okno->okno, &dolzina, &visina);
    dolzina /= 2;
    visina /= 2;
    x -= dolzina;
    y -= visina;
}
