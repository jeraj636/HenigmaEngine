#pragma once
#include "../../ostalo/ostalo.h"
#include <vector>
#include <string>
class Okno;
class Skupina;
class Scena
{
public:
    void zanka();
    Skupina *dodajSkupino(std::string ime);
    bool aktivno = 1;
    Scena(Okno *okn);
    ~Scena();

private:
    std::vector<Skupina *> tabSkupin;
    Okno *okno;
};