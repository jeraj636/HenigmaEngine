#pragma once
#include <cstdint>
// #include "../glad/include/glad/glad.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include "../ostalo/ostalo.h"
#include <map>
#include "../Scena/Scena.h"
class Render
{
public:
    Render();
    void Init(std::string ime);
    void Narisi(uint32_t tekstura);
    void DodajSceno(Scena *scena, std::string ime);
    void AktivirajSceno(std::string ime);
    uint32_t NaloziTeksturo(std::string pot);
    void Zanka();
    bool AliSeMoramZapreti();
    void OkvirZac();
    void OkvirKon();
    Barva Odzadje;

private:
Scena *m_aktivnaScena=NULL;
    std::map <std::string,Scena*>scene;
    GLFWwindow *m_okno;
    static void PosodobiVelOkna(GLFWwindow *okno, int dolzina, int visina);

    void DobiVhod();

    void NastaviBuferje();
    void NastaviShaderje();

    uint32_t m_SVBO;
    uint32_t m_SVAO;
    uint32_t m_SEBO;
    uint32_t m_shaderProgram;
};