#include <iostream>
#include "Render/Render.h"
#include "Scena/Scena.h"
#include "Scena/TestScena.h"
int main()
{
    std::cout << "Pozdravljen svet!\n";
    std::cout.flush();
    Render rend;
    TestScena test;
    rend.DodajSceno(test.Naslov(),"test");
    rend.AktivirajSceno("test");
    rend.Init("HenigmaEngine");
    uint32_t tek=rend.NaloziTeksturo("jakob");
    while (!rend.AliSeMoramZapreti())
    {
        rend.OkvirZac();
        rend.Zanka();
        rend.Narisi(tek);
        rend.OkvirKon();
    }
}