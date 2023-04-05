#pragma once
#include "../komponenta.h"
#include "../../ostalo/ostalo.h"

class Transformacija : public Komponenta
{
public:
    void zanka();
    Transformacija();
    Vec3 pozicija;
    Vec3 rotacija;
    Vec3 velikost;
};