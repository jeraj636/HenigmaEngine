#include "../Include/Risalnik.h"
#include "../Include/Log.h"
#include "../Include/Font.h"

#include <string>
#include <iostream>

int main()
{
    Risalnik::Init("Jakob");
    Risalnik::odzadje = 0x00ffffff;

    while (!Risalnik::AliSeMoramZapreti())
    {
        Risalnik::ZacetekFrame();
        Risalnik::KonecFrame();
    }
    Risalnik::Konec();
}