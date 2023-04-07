#include "../komponenta.h"
#include "../../matematika/matematika.h"
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
    void DobiPozicijoKazalca(double &x, double &y);
    void nastaviTocke(mat::vec::Vec2 &A, mat::vec::Vec2 &B, mat::vec::Vec2 &C, mat::vec::Vec2 &D);
    bool aliSemPritisnjen(mat::vec::Vec2 kazalec, float zAD, float zBc, float zDC, float zAB, float kDC, float kAD);
};