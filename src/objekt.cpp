#include <algorithm>
#include <cmath>
#include "../include/objekt.h"
#include "../include/risalnik.h"
void Objekt::nastavi(const mat::vec2 &poz, const mat::vec2 &vel, float rot, uint32_t barva_obj, uint32_t barva_ozd)
{
    pozicija = poz;
    velikost = vel;
    rotacija = rot;
    barva_objekta = barva_obj;
    barva_odzadja = barva_ozd;
    aktiven = true;
}

void Objekt::narisi_me()
{
    if (!aktiven)
        return;
    Risalnik::narisi(id_teksture, barva_objekta, barva_odzadja, pozicija, rotacija, velikost);
}

struct Lin_fun
{
    float k, n[2];
};
struct Tocke
{
public:
    mat::vec3 &operator[](int i)
    {
        return tab[i];
    }
    void Nastavi(const Objekt &o)
    {
        tab[0] = mat::vec3(-0.5f, -0.5f, 1.0f);
        tab[1] = mat::vec3(0.5f, -0.5f, 1.0f);
        tab[2] = mat::vec3(0.5f, 0.5f, 1.0f);
        tab[3] = mat::vec3(-0.5f, 0.5f, 1.0f);
        mat::mat::mat3 poz(1), rot(1), vel(1);
        mat::mat::Premik(o.pozicija, poz);
        mat::mat::Vrtilna(o.rotacija, rot);
        mat::mat::velikostna(o.velikost, vel);
        for (int i = 0; i < 4; i++)
        {
            tab[i] *= vel;
            tab[i] *= rot;
            tab[i] *= poz;
            // tab[i] *= Risalnik::get_orto();
        }
    }

private:
    mat::vec3 tab[4];
};
bool Objekt::trk(const Objekt &o)
{
    //! teluje zgolj za zaznavanje trkov toako da točke enega objekta sega v rugega
    //! če točka ne sega ta algoritem ne zazna./H
    Tocke t_tocke, o_tocke;
    t_tocke.Nastavi(*this);
    o_tocke.Nastavi(o);

    Lin_fun osnovna, pravokotna;
    osnovna.k = mat::fun::lin::K(t_tocke[0], t_tocke[1]);
    if (std::isinf(osnovna.k))
        osnovna.k = 10000;
    osnovna.n[0] = mat::fun::lin::N(osnovna.k, t_tocke[1]);
    osnovna.n[1] = mat::fun::lin::N(osnovna.k, t_tocke[2]);

    pravokotna.k = mat::fun::lin::K(t_tocke[0], t_tocke[3]);
    if (std::isinf(pravokotna.k))
        pravokotna.k = 10000;
    pravokotna.n[0] = mat::fun::lin::N(pravokotna.k, t_tocke[3]);
    pravokotna.n[1] = mat::fun::lin::N(pravokotna.k, t_tocke[2]);

    if (pravokotna.n[0] > pravokotna.n[1])
        std::swap(pravokotna.n[0], pravokotna.n[1]);

    if (osnovna.n[0] > osnovna.n[1])
        std::swap(osnovna.n[0], osnovna.n[1]);

    for (int i = 0; i < 4; i++)
    {
        float n_pravokoten, n_osnoven;
        n_pravokoten = mat::fun::lin::N(pravokotna.k, o_tocke[i]);
        n_osnoven = mat::fun::lin::N(osnovna.k, o_tocke[i]);
        if (n_pravokoten > pravokotna.n[0] && n_pravokoten < pravokotna.n[1] && n_osnoven > osnovna.n[0] && n_osnoven < osnovna.n[1])
            return true;
    }
    return false;
}
bool Objekt::je_miska_gor()
{
    Tocke t;
    t.Nastavi(*this);
    Lin_fun osnovna, pravokotna;

    osnovna.k = mat::fun::lin::K(t[0], t[1]);
    if (std::isinf(osnovna.k))
        osnovna.k = 10000;
    osnovna.n[0] = mat::fun::lin::N(osnovna.k, t[1]);
    osnovna.n[1] = mat::fun::lin::N(osnovna.k, t[2]);

    pravokotna.k = mat::fun::lin::K(t[0], t[3]);
    if (std::isinf(pravokotna.k))
        pravokotna.k = 10000;
    pravokotna.n[0] = mat::fun::lin::N(pravokotna.k, t[3]);
    pravokotna.n[1] = mat::fun::lin::N(pravokotna.k, t[2]);

    if (pravokotna.n[0] > pravokotna.n[1])
        std::swap(pravokotna.n[0], pravokotna.n[1]);

    if (osnovna.n[0] > osnovna.n[1])
        std::swap(osnovna.n[0], osnovna.n[1]);

    float n_pravokoten, n_osnoven;

    n_pravokoten = mat::fun::lin::N(pravokotna.k, Risalnik::get_poz_kazalca());
    n_osnoven = mat::fun::lin::N(osnovna.k, Risalnik::get_poz_kazalca());
    if (n_pravokoten > pravokotna.n[0] && n_pravokoten < pravokotna.n[1] && n_osnoven > osnovna.n[0] && n_osnoven < osnovna.n[1])
        return true;
    return false;
}
void Objekt_anim::narisi_me()
{
    if (animacije[trenutna_animacija].naslednji <= Cas::get_time())
    {
        animacije[trenutna_animacija].stopnja_animacije++;
        if (animacije[trenutna_animacija].stopnja_animacije >= animacije[trenutna_animacija].tekstura_id.size())
        {
            animacije[trenutna_animacija].stopnja_animacije = 0;
            trenutna_animacija = animacije[trenutna_animacija].naslednja_animacija;
        }
        id_teksture = animacije[trenutna_animacija].tekstura_id[animacije[trenutna_animacija].stopnja_animacije];

        animacije[trenutna_animacija].naslednji = Cas::get_time() + animacije[trenutna_animacija].perioda;
    }
    Objekt::narisi_me();
}

void Objekt::unici()
{
    Risalnik::skenslaj_teksturo(&id_teksture);
}