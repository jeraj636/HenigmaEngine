#pragma once
#include <cstdint>
// #include "../glad/include/glad/glad.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include "../ostalo/ostalo.h"
class Render
{
public:
    Render(std::string ime);
    void Init(std::string ime);
    void Narisi();
    // void DodajSceno();
    // void AktivirajSceno();
    // uint32_t NaloziTeksturo();
    void Zanka();
    bool AliSeMoramZapreti();
    void OkvirZac();
    void OkvirKon();
    Barva Odzadje;

private:
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