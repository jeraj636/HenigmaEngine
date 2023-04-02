#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "ostalo/ostalo.h"
#include <iostream>
#include "renderer/renderer.h"
#include "podEnote/scena/scena.h"
#include "podEnote/skupina/skupina.h"
#include "objekt/objekt.h"
#include "komponente/kompinenta.h"
#include "komponente/upodabljalnik/upodabljalnik.h"
int main()
{
    Okno okno(800, 600, "HenigmeEngine");
    Barva b(0xffff00ff);
    Scena *glavna = okno.dodajSceno();
    Skupina *sk = glavna->dodajSkupino();
    Objekt *t = sk->dodajObjekt("t");
    t->dodajKomponento<Upodabljalnik>();
    sk->poisciObjekt("t")->poisciKOmponento<Upodabljalnik>()->aktivno = 0;
    while (!glfwWindowShouldClose(okno.okno))
    {

        okno.zanka();
    };
    glfwTerminate();
    return 0;
}
