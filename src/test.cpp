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
    uint32_t Kokos = Risalnik::NaloziTeksturo("kokos.png");

    Font courier = Risalnik::NaloziFont("font.ttf", 20);
    for (int i = 0; i < 128; i++)
        std::cout << courier.DobiZnak(i).tekID << std::endl;
    Risalnik::odzadje = 0x000000ff;
    vec3 poz(100.0f, 100.0f, 0.0f), vel(100.0f, 100.0f, 0.0f);
    Barva spredi(0xff0000ff);
    Barva zadi(0xff0000ff);
    while (!Risalnik::AliSeMoramZapreti())
    {
        Risalnik::ZacetekFrame();
        Risalnik::NarisiZnak(courier.DobiZnak('j'), spredi, zadi, poz + 300, 0, 15);
        Risalnik::Narisi(Kokos, spredi, zadi, poz, 90, vel);
        Risalnik::KonecFrame();
    }
}