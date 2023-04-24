#include "scena.h"
#include "../../renderer/renderer.h"
#include "../skupina/skupina.h"
void Scena::zanka()
{
    for (int i = 0; i < tabSkupin.size(); i++)
    {
        if (tabSkupin[i]->aktivno)
            tabSkupin[i]->zanka();
    }
}
Skupina *Scena::dodajSkupino(std::string ime)
{
    tabSkupin.push_back(new Skupina(okno, ime));
    return tabSkupin.back();
}
Scena::Scena(Okno *okn)
{
    okno = okn;
}
Scena::~Scena()
{
    for (int i = 0; i < tabSkupin.size(); i++)
        delete tabSkupin[i];
}
