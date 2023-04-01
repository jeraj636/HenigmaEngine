#pragma once
#include "../../ostalo/ostalo.h"
#include <vector>
class Okno;
class Skupina;
class Scena
{
public:
    void zanka();
    Skupina *dodajSkupino();
    bool aktivno = 1;
    std::vector<Skupina *> tabSkupin;
    Okno *okno;
    Scena(Okno *okn);
};