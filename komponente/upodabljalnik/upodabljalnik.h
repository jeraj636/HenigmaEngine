#pragma once
#include "../komponenta.h"
#include "../../ostalo/ostalo.h"
class Upodabljalnik : public Komponenta
{
public:
    void zanka();
    Upodabljalnik();

    Barva barvaOdzadja;
    Barva barvaObjekta;
    uint tekstura;
};