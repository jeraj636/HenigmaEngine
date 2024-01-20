#include "../include/henigma_engine.h"

int main()
{
    Risalnik::init("test", mat::vec2(30, 30));
    while (!Risalnik::ali_se_moram_zapreti())
    {
        Risalnik::zacetek_okvir();
        Risalnik::narisi_niz(Font("../test.ttf", 50), Barva(0xffffffff), Barva(0), 1080 / 2, 500, "Morski smetar");
        Risalnik::konec_okvir();
    }
    Risalnik::konec();
}