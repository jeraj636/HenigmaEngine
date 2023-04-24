#include "../komponenta.h"
#include "../../matematika/matematika.h"
#include "../../ostalo/ostalo.h"
#include <string>
#include <vector>

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
    std::string vsebina;
    Barva barvaOdzadja;
    Barva barvaObjekta;
    Besedilo();
    unsigned int pisava;

private:
    // float lokacija['~' - '!'];

        std::vector<mat::vec::Vec2 *> lokacija;
};