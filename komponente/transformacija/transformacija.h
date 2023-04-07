#pragma once
#include "../komponenta.h"
#include "../../ostalo/ostalo.h"
#include "../../matematika/matematika.h"
class Transformacija : public Komponenta
{
public:
    void zanka();
    Transformacija();

    mat::vec::Vec3 pozicija;
    mat::vec::Vec3 rotacija;
    mat::vec::Vec3 velikost;
};