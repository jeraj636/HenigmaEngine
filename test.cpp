
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
    Barva b(0x000000ff);
    okno.barvaOdzadja = b;
    Barva obj(0xff00ffff);
    Barva ozd(0xffff00ff);
    Scena *glavna = okno.dodajSceno();
    Skupina *sk = glavna->dodajSkupino("sk");
    Objekt *test = sk->dodajObjekt("test");
    //test->poisciKomponento<Transformacija>()->velikost = mat::vec::Vec3(25, 15, 0);
    test->poisciKomponento<Transformacija>()->velikost = mat::vec::Vec3(100, 90, 0);
    test->dodajKomponento<Besedilo>();
    test->poisciKomponento<Besedilo>()->naloziPisavo("bitmap/a.bmp");
    test->poisciKomponento<Besedilo>()->vsebina = "Jakob";
    test->poisciKomponento<Besedilo>()->barvaObjekta = obj;
    test->poisciKomponento<Besedilo>()->barvaOdzadja = ozd;
    sk->uniciObjekt(test);
    while (!glfwWindowShouldClose(okno.okno))
    {
        okno.zanka();
    };
    glfwTerminate();
    return 0;
}
