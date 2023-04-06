#include "skupina.h"
#include "../../renderer/renderer.h"
#include "../../ostalo/ostalo.h"
#include "../../objekt/objekt.h"
void Skupina::zanka()
{
    for (int i = 0; i < tabObjektov.size(); i++)
    {
        if (tabObjektov[i]->aktivno)
            tabObjektov[i]->zanka();
    }
    for (int i = 0; i < tabSkupn.size(); i++)
        if (tabSkupn[i]->aktivno)
            tabSkupn[i]->zanka();
}
Objekt *Skupina::dodajObjekt(std::string ime)
{
    tabObjektov.push_back(new Objekt(okno, ime));
    return tabObjektov.back();
}
Skupina::Skupina(Okno *okn, std::string _ime)
{
    okno = okn;
    ime = _ime;
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
Skupina *Skupina::dodajSkupino(std::string ime)
{
    tabSkupn.push_back(new Skupina(okno, ime));
    return tabSkupn.back();
}
Skupina *Skupina::poisciSkupinoo(std::string ime)
{
    for (int i = 0; i < tabSkupn.size(); i++)
    {
        if (tabSkupn[i]->ime == ime)
            return tabSkupn[i];
    }
    return nullptr;
}
Skupina::~Skupina()
{
    for (int i = 0; i < tabSkupn.size(); i++)
        delete tabSkupn[i];
    for (int i = 0; i < tabObjektov.size(); i++)
        delete tabObjektov[i];
}