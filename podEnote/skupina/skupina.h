#pragma once
#include <vector>
#include "../../ostalo/ostalo.h"
#include "../../objekt/objekt.h"
#include <string>
class Okno;
class Skupina
{
public:
    Okno *okno;

    bool aktivno = 1;
    std::string ime;

    std::vector<Objekt *> tabObjektov;
    std::vector<Skupina *> tabSkupn;

    Objekt *dodajObjekt(std::string ime);
    Objekt *poisciObjekt(std::string ime);

    Skupina *dodajSkupino(std::string ime);
    Skupina *poisciSkupinoo(std::string ime);

    Skupina(Okno *okn, std::string _ime);
    void zanka();
    ~Skupina();
};