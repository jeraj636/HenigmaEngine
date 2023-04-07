#include "../komponenta.h"

class Transformacija;
class Okno;
class Objekt;

class Gumb : public Komponenta
{
public:
    void zanka();
    Transformacija *tr;
    void nastavi(Okno *okn, Objekt *obj);

private:
    void DobiPozicijoKazalca(int &x, int &y);
};