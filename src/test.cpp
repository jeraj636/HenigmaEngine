#include <iostream>
#include "Render/Render.h"
#include "Scena/Scena.h"
#include "Scena/TestScena.h"
#include "Matematika/Matematika.h"

#include "ostalo/ostalo.h"
int main()
{
    Render rend;
    rend.Init("HenigmaEngine");

    // spl::io::err("hoj");

    TestScena test;
    rend.DodajSceno(test.Naslov(), "test");
    rend.AktivirajSceno("test");

    Font bold;
    uint32_t tek = rend.NaloziTeksturo("Materiali/Slike/logo260.png");
    bold.NaloziFont("../Materiali/Font/CourierPrime-Regular.ttf", 500);

    spl::vec3 poz(400.0f, 300.0f, 0);
    spl::vec3 vel(10.0f, 10.0f, 1);
    float rot = 0;
    Barva SP(0xffff00ff), OZ(0xffffff00);
    char c = ' ';
    float naslednji = glfwGetTime() + 1;
    while (!rend.AliSeMoramZapreti())
    {
        rend.OkvirZac();
        rend.Zanka();
        /*
        if (naslednji <= glfwGetTime())
        {
            c++;
            if (c >= 128)
                c = ' ';
            naslednji = glfwGetTime() + 1;
        }*/

        // rend.Narisi(tek, poz, sin(glfwGetTime()) * 360, vel, OZ, SP);
        // rend.NarisiZnak(bold.znaki['Z'], poz, rot, SP, OZ);
        // rend.NarisiZnak(bold.znaki['z'], poz + spl::vec3(50, 0, 0), rot, SP, OZ);
        rend.NarisiNiz("Pozdravljen Svet", bold, poz, rot, vel, SP, OZ);
        rend.OkvirKon();
    }
}