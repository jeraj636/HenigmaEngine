#include "../Include/Risalnik.h"
#include "../Include/Log.h"
#include "../Include/Font.h"

#include <string>
#include <iostream>

int main()
{
    io::msg("DELA");
    Risalnik::Init("jakob");

    Risalnik::sredstvaPath = "../Sredstva";
    Font courier = Risalnik::NaloziFont("font.ttf", 20);

    Barva spredi(0xff00ffff), zadi(0xffff00ff);
    vec3 poz(300, 150, 0), vel(100, 100, 0);
    float rot = 0;
    uint32_t kokos = Risalnik::NaloziTeksturo("kokos.png");
    Risalnik::odzadje = 0x000000ff;
    while (!Risalnik::AliSeMoramZapreti())
    {
        Risalnik::ZacetekFrame();
        Risalnik::NarisiZnak(courier.DobiZnak('J'), spredi, zadi, poz + vec3(100, 100, 0), 0, 15);
        Risalnik::Narisi(kokos, spredi, zadi, poz, rot, vel);
        Risalnik::KonecFrame();
    }
}