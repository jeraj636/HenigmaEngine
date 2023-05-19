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
    spl::vec3 poz(0.5f, 0.5f, 0);
    spl::vec3 vel(0.5f, 0.5f, 1);
    float rot = 0;
    Barva SP(0xff00ffff), OZ(0x000000ff);

    while (!rend.AliSeMoramZapreti())
    {
        rend.OkvirZac();
        rend.Zanka();
        rend.Narisi(tek, poz, rot, vel, SP, OZ);
        rend.OkvirKon();
    }
}