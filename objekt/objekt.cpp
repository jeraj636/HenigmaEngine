#include "objekt.h"
#include "../renderer/renderer.h"
#include "../komponente/kompinenta.h"
#include <vector>
Objekt::Objekt(Okno *okn, std::string _ime)
{
    okno = okn;
    ime = _ime;
}
void Objekt::zanka()
{

    for (int i = 0; i < tabKomponent.size(); i++)
    {
        if (tabKomponent[i]->aktivno)
            tabKomponent[i]->zanka();
    }
}