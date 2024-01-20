#include "../include/henigma_engine.h"

int main()
{
    Risalnik::init("test", mat::vec2(30, 30));
    while (!Risalnik::ali_se_moram_zapreti())
    {
        Risalnik::zacetek_okvir();
        Risalnik::narisi_niz(Font("../test.ttf", 50), Barva(0xffffffff), Barva(0), mat::vec2(-300, 0), 500, "pozz svet");
        Risalnik::konec_okvir();
    }
    Risalnik::konec();
}