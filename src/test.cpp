#include <iostream>
#include "Render/Render.h"
#include "Scena/Scena.h"
#include "Scena/TestScena.h"
#include "Matematika/Matematika.h"
int main()
{
    Render rend;
    rend.Init("HenigmaEngine");

    TestScena test;
    rend.DodajSceno(test.Naslov(), "test");
    rend.AktivirajSceno("test");

    uint32_t tek = rend.NaloziTeksturo("jakob");

    while (!rend.AliSeMoramZapreti())
    {
        rend.OkvirZac();
        rend.Zanka();
        rend.Narisi(tek);
        rend.OkvirKon();
    }
}