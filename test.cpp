
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

    test->poisciKomponento<Transformacija>()->velikost = mat::vec::Vec2(200, 400);
    test->poisciKomponento<Transformacija>()->pozicija.x = -700;
    test->dodajKomponento<Gumb>();

    test->dodajKomponento<Besedilo>();

    Besedilo *bes = test->poisciKomponento<Besedilo>();
    bes->naloziPisavo("bitmap/a.png");
    bes->vsebina = "Jakob";
    bes->vsebina = " ";

    bes->barvaObjekta = Barva(0xff0000ff);
    bes->barvaOdzadja = Barva(0x00ff00ff);
    test->dodajKomponento<Gumb>();
    // test->poisciKomponento<Transformacija>()->rotacija.z = 180;
    float konc = glfwGetTime() + 0.5;
    while (!glfwWindowShouldClose(okno.okno))
    {

        if (glfwGetTime() >= konc)
        {
            konc = glfwGetTime() + 0.5;
            bes->vsebina[0]++;
            if (bes->vsebina[0] == '~')
                bes->vsebina[0] = ' ';
        }

        okno.zanka();
    };
    glfwTerminate();
    return 0;
}
