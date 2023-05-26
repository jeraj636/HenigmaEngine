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
    bold.NaloziFont("../Materiali/Font/CourierPrime-Bold.ttf",500);


    spl::vec3 poz(400.0f, 300.0f, 0);
    spl::vec3 vel(10.0f, 10.0f, 1);
    float rot = 0;
    Barva SP(0xffff00ff), OZ(0xffffff00);

    while (!rend.AliSeMoramZapreti())
    {
        rend.OkvirZac();
        rend.Zanka();
       // rend.Narisi(tek, poz, sin(glfwGetTime()) * 360, vel, OZ, SP);
       rend.NarisiZnak(bold.znaki['J'].TeksturaID,poz,sin(glfwGetTime())*180,vel,SP,OZ);
        rend.OkvirKon();
    }
}