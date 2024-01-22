#ifndef PLOSCICE_H
#define PLOSCICE_H

#include <vector>
#include <stdint.h>
#include <matematika/matematika.h>
#include "barva.h"

class Ploscice
{
public:
    uint32_t tekstura_id;
    mat::vec2 velikost;
    Barva barva_objekta;

public:
    void nastavi(char *zemljevid, int x, int y, char prepoznavni_znak, uint32_t tek_id, uint32_t barva_obj);
    void narisi_me();
    void unici();
    Ploscice();

private:
    float *m_tocke;
    uint32_t *m_indeksi;
    int m_n;
};

#endif