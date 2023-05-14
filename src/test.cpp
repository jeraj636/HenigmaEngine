#include <iostream>
#include "Render/Render.h"
int main()
{
    std::cout << "Pozdravljen svet!\n";
    Render rend("HenigmaEngine");
    rend.Init("HenigmaEngine");
    while (!rend.AliSeMoramZapreti())
    {
        rend.OkvirZac();
        rend.Zanka();
        rend.Narisi();
        rend.OkvirKon();
    }
}