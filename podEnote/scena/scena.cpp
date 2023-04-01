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
Skupina *Scena::dodajSkupino()
{
    tabSkupin.push_back(new Skupina(okno));
    return tabSkupin.back();
}
Scena::Scena(Okno *okn)
{
    okno = okn;
}