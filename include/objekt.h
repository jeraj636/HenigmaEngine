#ifndef OBJEKT_H
#define OBJEKT_H

#include <matematika/matematika.h>
#include <stdint.h>
#include <vector>
#include "barva.h"
class Objekt
{
public:
    Barva barva_objekta;
    Barva barva_odzadja;
    mat::vec2 velikost;
    mat::vec2 pozicija;
    float rotacija;
    bool aktiven;
    uint32_t id_teksture;

public:
    void nastavi(const mat::vec2 &poz, const mat::vec2 &vel, float rot, uint32_t barva_ojb, uint32_t barva_ozd);
    Objekt() = default;
    void narisi_me();
    bool trk(const Objekt &o);
    bool je_miska_gor();
    void unici();
};

class Objekt_anim;

class Animacija
{
public:
    std::vector<uint32_t> tekstura_id;
    double perioda;
    int naslednja_animacija;

protected:
    int stopnja_animacije;
    double naslednji;
    friend class Objekt_anim;
};
class Objekt_anim : public Objekt
{
public:
    std::vector<Animacija> animacije;
    int trenutna_animacija;

public:
    void narisi_me();
};
#endif
