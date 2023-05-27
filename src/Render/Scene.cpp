#include "Render.h"

void Render::DodajSceno(Scena *scena, const std::string &ime)
{
    scene.insert({ime, scena});
}
void Render::AktivirajSceno(const std::string &ime)
{
    if (m_aktivnaScena != nullptr)
        m_aktivnaScena->Konec();
    auto najdeno = scene[ime];

    m_aktivnaScena = najdeno;
    m_aktivnaScena->Zacetek();
}