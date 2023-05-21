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

    uint32_t tek = rend.NaloziTeksturo("Materiali/Slike/logo260.png");
    spl::vec3 poz(400.0f, 300.0f, 0);
    spl::vec3 vel(50.0f, 50.0f, 1);
    float rot = 0;
    Barva SP(0xff0000ff), OZ(0xffffff00);

    while (!rend.AliSeMoramZapreti())
    {
        rend.OkvirZac();
        rend.Zanka();
        rend.Narisi(tek, poz, sin(glfwGetTime()) * 360, vel, OZ, SP);
        rend.OkvirKon();
    }
}