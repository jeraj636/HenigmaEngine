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
Objekt *Skupina::dodajObjekt(std::string ime)
{
    tabObjektov.push_back(new Objekt(okno, ime));
    return tabObjektov.back();
}
Skupina::Skupina(Okno *okn)
{
    okno = okn;
}
Objekt *Skupina::poisciObjekt(std::string ime)
{
    for (int i = 0; i < tabObjektov.size(); i++)
    {
        if (tabObjektov[i]->ime == ime)
            return tabObjektov[i];
    }
    return nullptr;
}