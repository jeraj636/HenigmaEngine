#include "Risalnik/Risalnik.h"
#include <string>
int main()
{
    Risalnik::Init("jakob");
    while (!Risalnik::AliSeMoramZapreti())
    {
        Risalnik::Zanka();
    }
}