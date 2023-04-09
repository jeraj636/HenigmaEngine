#include "../komponenta.h"
class Transformacija;
class Okno;
class Objekt;

class Besedilo : public Komponenta
{
public:
    void zanka();
    void nastavi(Okno *okn, Objekt *obj);
    unsigned int font;

private:
};