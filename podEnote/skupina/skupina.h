#pragma once
#include <vector>
#include <string>
#include "../../matematika/matematika.h"

class Okno;
class Objekt;
class Skupina
{
public:
    bool aktivno = 1;
    std::string ime;
    void uniciObjekt(Objekt *obj);
    Objekt *dodajObjekt(std::string ime);
    Objekt *poisciObjekt(std::string ime);
    mat::vec::Vec3 pozicija;
    Skupina(Okno *okn, std::string _ime);
    void zanka();
    ~Skupina();

private:
    Okno *okno;
    std::vector<Skupina *> tabSkupn;
    std::vector<Objekt *> tabObjektov;
};