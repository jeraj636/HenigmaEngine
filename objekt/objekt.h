#pragma once
#include <vector>
#include "../komponente/upodabljalnik/upodabljalnik.h"
#include "../komponente/transformacija/transformacija.h"
#include "../komponente/komponenta.h"
#include <string>
class Okno;
class Komponenta;
class Objekt
{
public:
    Objekt(Okno *okn, std::string _ime);
    void zanka();
    bool aktivno = 1;
    template <class t>
    void dodajKomponento()
    {
        tabKomponent.push_back(new t);
        tabKomponent.back()->nastavi(okno, this);
    }
    template <class t>
    t *poisciKomponento()
    {
        for (int i = 0; i < tabKomponent.size(); i++)
        {
            if (dynamic_cast<t *>(tabKomponent[i]) != nullptr)
                return (t *)tabKomponent[i];
        }
        return nullptr;
    }
    std::string ime;
    ~Objekt();

private:
    std::vector<Komponenta *> tabKomponent;
    Okno *okno;
};