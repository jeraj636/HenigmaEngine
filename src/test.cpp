#include <iostream>
#include "Render/Render.h"
int main()
{
    std::cout << "Pozdravljen svet!\n";
    std::cout.flush();
    Render rend;
    rend.Init("HenigmaEngine");
    uint32_t tek=rend.NaloziTeksturo("jakob");
    while (!rend.AliSeMoramZapreti())
    {
        rend.OkvirZac();
        rend.Zanka();
        rend.Narisi(tek);
        rend.OkvirKon();
    }
}