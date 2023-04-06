#include "objekt.h"
#include "../renderer/renderer.h"

Objekt::Objekt(Okno *okn, std::string _ime)
{
    okno = okn;
    ime = _ime;
    this->dodajKomponento<Transformacija>();
}
void Objekt::zanka()
{

    for (int i = 0; i < tabKomponent.size(); i++)
    {
        if (tabKomponent[i]->aktivno)
            tabKomponent[i]->zanka();
    }
}
Objekt::~Objekt()
{
    for (int i = 0; i < tabKomponent.size(); i++)
        delete tabKomponent[i];
}