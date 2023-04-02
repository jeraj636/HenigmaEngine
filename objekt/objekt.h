#pragma once
#include <vector>
#include "../komponente/upodabljalnik/upodabljalnik.h"
// #include "../komponente/kompinenta.h"
#include <string>
class Okno;
class Komponenta;
class Objekt
{
public:
    Okno *okno;
    Objekt(Okno *okn, std::string _ime);
    void zanka();
    bool aktivno = 1;
    std::vector<Komponenta *> tabKomponent;
    template <class t>
    void dodajKomponento()
    {
        tabKomponent.push_back(new t);
        tabKomponent.back()->nastavi(okno, this);
    }
    template <class t>
    Komponenta *poisciKOmponento()
    {
        for (int i = 0; i < tabKomponent.size(); i++)
        {
            if (dynamic_cast<t *>(tabKomponent[i]) != nullptr)
                return tabKomponent[i];
        }
        return nullptr;
    }
    std::string ime;

private:
};