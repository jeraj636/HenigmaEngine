#include "besedilo.h"
#include "../../renderer/renderer.h"
#include "../../objekt/objekt.h"
#include "../../ostalo/ostalo.h"
void Besedilo::zanka()
{
}
void Besedilo::nastavi(Okno *okn, Objekt *obj)
{
    io::izpis("objekt je nastavljen", io::type::msg);
    okno = okn;
    objekt = obj;
}
