#include "../include/henigma_engine.h"

int main()
{
    Risalnik::init("test", mat::vec2(30, 30));
    Risalnik::sredstva_pot = "../";
    Objekt a, b, c;
    uint32_t tek = Risalnik::nalozi_teksturo("ploscica.png");
    a.id_teksture = b.id_teksture = c.id_teksture = tek;
    Font t("../test.ttf", 50);
    b.nastavi(mat::vec2(600, 600), mat::vec2(100, 100), 45, 0xfff00fff, 0);
    c.nastavi(mat::vec2(200, 200), mat::vec2(100, 100), 0, 0x00ffffff, 0);
    a.nastavi(mat::vec2(200, 200), mat::vec2(100, 100), 0, 0x00ffffff, 0);
    Objekt_anim tt;
    tt.nastavi(mat::vec2(900, 900), mat::vec2(100, 100), 0, 0xffffffff, 0);
    Animacija tam;
    tam.tekstura_id.push_back(Risalnik::nalozi_teksturo("ploscica.png"));
    tam.tekstura_id.push_back(Risalnik::nalozi_teksturo("smet.png"));
    tam.perioda = 1;
    tam.naslednja_animacija = 0;
    tt.trenutna_animacija = 0;
    tt.animacije.push_back(tam);
    while (!Risalnik::ali_se_moram_zapreti())
    {
        Risalnik::zacetek_okvir();
        a.pozicija = Risalnik::get_poz_kazalca();
        if (b.trk(a) || a.trk(b))
            c.narisi_me();
        b.narisi_me();
        a.narisi_me();
        tt.narisi_me();
        Risalnik::narisi_niz(t, Barva(0xffffffff), Barva(0), 1080 / 2, 500, "Morski smetar");
        Risalnik::konec_okvir();
    }
    Risalnik::konec();
}