#include "skupina.h"
#include "../../renderer/renderer.h"
void Skupina::zanka()
{
    for (int i = 0; i < tabObjektov.size(); i++)
    {
        if (tabObjektov[i]->aktivno)
            tabObjektov[i]->zanka();
    }
}
Objekt *Skupina::dodajObjekt()
{
    tabObjektov.push_back(new Objekt(okno));
    return tabObjektov.back();
}
Skupina::Skupina(Okno *okn)
{
    okno = okn;
}