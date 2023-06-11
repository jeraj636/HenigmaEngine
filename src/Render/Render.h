#pragma once
#include <cstdint>
// #include "../glad/include/glad/glad.h"
#include "../glad/include/glad/glad.h"
#include <GLFW/glfw3.h>
#include <string>
#include "../ostalo/ostalo.h"
#include <map>
#include "../Scena/Scena.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../Matematika/Matematika.h"

//* neumno poimenovanje
class Okno
{
public:
    int visina, dolzina;
};

//* neumno poimenovanje
class Kazalec
{
public:
    double x, y;
};

struct Znak
{
    uint32_t TeksturaID;
    uint32_t odmik;
    spl::vec2 ofset;
    spl::vec2 velikost;
};

class Font
{
public:
    Font();
    Font(const std::string &pot, int velikost);
    void NaloziFont(const std::string &pot, int velikost);

    Znak znaki[128];

private:
};

class Render
{
public:
    Render();
    void Init(const std::string &ime);
    void Narisi(uint32_t &tekstura, spl::vec3 poz, float rot, spl::vec3 vel, Barva BObj = Barva(0xffffffff), Barva BOzd = Barva(0xffffffff));
    void NarisiZnak(Znak &znak, spl::vec3 poz, float rot, Barva BObj = Barva(0xffffffff), Barva BOzd = Barva(0x000000ff));
    void NarisiNiz(const std::string &vsebina, Font &font, spl::vec3 poz, float rot, spl::vec3 vel, Barva BObj, Barva BOzd = Barva(0x000000ff));
    void DodajSceno(Scena *scena, const std::string &ime);
    void AktivirajSceno(const std::string &ime);
    uint32_t NaloziTeksturo(const std::string &pot);
    void Zanka();
    bool AliSeMoramZapreti();
    void OkvirZac();
    void OkvirKon();
    Barva Odzadje;
    Okno okno;
    Kazalec kazalec;
    static char trenutenZnak;

private:
    Scena *m_aktivnaScena = NULL;
    std::map<std::string, Scena *> scene;
    GLFWwindow *m_okno;
    glm::mat4 m_proj;
    static void PosodobiVelOkna(GLFWwindow *okno, int dolzina, int visina);
    static void CharCallBack(GLFWwindow *okno, uint32_t znak);
    void BindajStaticneBufferje();
    void BindajDinamicneBufferje();
    void DobiVhod();

    void NastaviBuferje();
    void NastaviShaderje();

    uint32_t m_SVBO;
    uint32_t m_SVAO;
    uint32_t m_SEBO;

    uint32_t m_shaderProgram;
    uint32_t m_shaderProgramBes;
};