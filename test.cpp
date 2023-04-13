
#include "ostalo/ostalo.h"
#include <iostream>
#include "renderer/renderer.h"
#include "podEnote/scena/scena.h"
#include "podEnote/skupina/skupina.h"
#include "objekt/objekt.h"
#include "komponente/komponenta.h"
#include "komponente/upodabljalnik/upodabljalnik.h"
#include "komponente/transformacija/transformacija.h"
#include "komponente/gumb/gumb.h"
#include "komponente/besedilo/besedilo.h"
#include "cmath"
#include "unistd.h"
#include <string>
#include "matematika/matematika.h"
int main()
{
    Okno okno(800, 600, "HenigmeEngine");
    Barva b(0xffff00ff);
    okno.barvaOdzadja = b;
    Scena *glavna = okno.dodajSceno();
    Skupina *sk = glavna->dodajSkupino("sk");
    Objekt *test = sk->dodajObjekt("test");
    test->dodajKomponento<Upodabljalnik>();
    test->poisciKomponento<Upodabljalnik>()->tekstura = naloziTeksturo("bitmap/CourierPrime.png", 0);
    test->poisciKomponento<Upodabljalnik>()->aktivno = 0;
    test->poisciKomponento<Upodabljalnik>()->barvaOdzadja = Barva(0xffffffff);
    test->poisciKomponento<Upodabljalnik>()->barvaObjekta = Barva(0xff0000ff);
    test->poisciKomponento<Transformacija>()->velikost = mat::vec::Vec2(200, 400);
    test->dodajKomponento<Gumb>();
    test->dodajKomponento<Besedilo>();
    Besedilo *bes = test->poisciKomponento<Besedilo>();
    bes->vsebina = ' ';
    bes->naloziPisavo("bitmap/a.png");
    bes->barvaObjekta = Barva(0xff0000ff);
    bes->barvaOdzadja = Barva(0x00ff00ff);
    test->dodajKomponento<Gumb>();
    // test->poisciKomponento<Transformacija>()->rotacija.z = 180;
    float koncas = glfwGetTime() + 0.5;
    while (!glfwWindowShouldClose(okno.okno))
    {
        if (glfwGetTime() >= koncas)
        {
            bes->vsebina++;
            koncas = glfwGetTime() + 0.5;
        }
        if (bes->vsebina >= 'Z' - 'A')
            bes->vsebina = 0;
        if (test->poisciKomponento<Gumb>()->aliSemPritisnjen)
            test->poisciKomponento<Transformacija>()->rotacija.z = tan(glfwGetTime()) * 360;
        okno.zanka();
    };
    glfwTerminate();
    return 0;
}
