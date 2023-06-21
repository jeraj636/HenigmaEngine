#include "../Include/Risalnik.h"
#include "../Include/Log.h"
#include <string>

int main()
{
    io::msg("DELA");
    Risalnik::Init("jakob");
    Risalnik::sredstvaPath = "../Sredstva";
    uint32_t Kokos = Risalnik::NaloziTeksturo("kokos.png");

    Risalnik::odzadje = 0x000000ff;
    vec3 poz(100.0f, 100.0f, 0.0f), vel(100.0f, 100.0f, 0.0f);
    Barva spredi(0xff0000ff);
    Barva zadi(0xff0000ff);
    while (!Risalnik::AliSeMoramZapreti())
    {
        Risalnik::ZacetekFrame();
        Risalnik::Narisi(Kokos, spredi, zadi, poz, 90, vel);
        Risalnik::KonecFrame();
    }
}