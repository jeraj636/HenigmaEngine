
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
#include "cmath"
int main()
{
    Okno okno(800, 600, "HenigmeEngine");
    Barva b(0xffff00ff);
    okno.barvaOdzadja = b;
    Scena *glavna = okno.dodajSceno();
    Skupina *sk = glavna->dodajSkupino("sk");
    Objekt *test = sk->dodajObjekt("test");
    test->dodajKomponento<Upodabljalnik>();
    test->dodajKomponento<Gumb>();
    test->poisciKomponento<Upodabljalnik>()->tekstura = naloziTeksturo("chicken.png");
    //  test->poisciKomponento<Transformacija>()->rotacija.z = 90;
    test->poisciKomponento<Transformacija>()->pozicija.x = 0;
    test->poisciKomponento<Transformacija>()->velikost.y = 100;
    test->poisciKomponento<Transformacija>()->velikost.x = 100;
    test->poisciKomponento<Transformacija>()->rotacija.z = 180;

    while (!glfwWindowShouldClose(okno.okno))
    {
        okno.zanka();
        // test->poisciKomponento<Transformacija>()->rotacija.z = sin(glfwGetTime()) * 180 * 2;
    };
    glfwTerminate();
    return 0;
}
