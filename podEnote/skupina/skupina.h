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
    std::string ime;

    Objekt *dodajObjekt(std::string ime);
    Objekt *poisciObjekt(std::string ime);

    Skupina *dodajSkupino(std::string ime);
    Skupina *poisciSkupinoo(std::string ime);

    Skupina(Okno *okn, std::string _ime);
    void zanka();
    ~Skupina();

private:
    Okno *okno;
    std::vector<Skupina *> tabSkupn;
    std::vector<Objekt *> tabObjektov;
};