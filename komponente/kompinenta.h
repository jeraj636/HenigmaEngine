#pragma once
#include "upodabljalnik/upodabljalnik.h"
#include "transformacija/transformacija.h"
class Okno;
class Objekt;
class Komponenta
{
public:
    virtual void zanka()
    {
    }
    void nastavi(Okno *okn, Objekt *obj)
    {
        okno = okn;
        objekt = obj;
    }
    Okno *okno;
    Objekt *objekt;
    bool aktivno = 1;

private:
};