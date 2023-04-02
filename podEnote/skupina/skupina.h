#pragma once
#include <vector>
#include "../../ostalo/ostalo.h"
#include "../../objekt/objekt.h"
#include <string>
class Okno;
class Skupina
{
public:
    bool aktivno = 1;
    void zanka();
    std::vector<Objekt *> tabObjektov;
    Objekt *dodajObjekt(std::string ime);
    Okno *okno;
    Skupina(Okno *okn);
    Objekt *poisciObjekt(std::string ime);
};