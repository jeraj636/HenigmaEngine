
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
    test->poisciKomponento<Transformacija>()->velikost = mat::vec::Vec3(100, 100, 0);
    test->poisciKomponento<Upodabljalnik>()->barvaObjekta = Barva(0xff000000);
    test->poisciKomponento<Upodabljalnik>()->barvaOdzadja = Barva(0xff0000ff);
    // bes->barvaObjekta = Barva(0xff0000ff);
    // bes->barvaOdzadja = Barva(0x00ff00ff);

    while (!glfwWindowShouldClose(okno.okno))
    {
        okno.zanka();
    };
    glfwTerminate();
    return 0;
}
