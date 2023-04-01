#pragma once
#include <vector>
#include "../../ostalo/ostalo.h"
#include "../../objekt/objekt.h"
class Okno;
class Skupina
{
public:
    bool aktivno = 1;
    void zanka();
    std::vector<Objekt *> tabObjektov;
    Objekt *dodajObjekt();
    Okno *okno;
    Skupina(Okno *okn);
};