#include "../komponenta.h"
#include "../../matematika/matematika.h"
#include "../../ostalo/ostalo.h"
#include <string>
class Transformacija;
class Okno;
class Objekt;

class Besedilo : public Komponenta
{
public:
    void zanka();
    void nastavi(Okno *okn, Objekt *obj);
    // unsigned int font;
    void naloziPisavo(const char *potDoPisave);
    char vsebina;
    Barva barvaOdzadja;
    Barva barvaObjekta;
    Besedilo();

private:
    unsigned int _pisiava;
    float lokacija[26];
};