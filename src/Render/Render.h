#pragma once
#include <cstdint>
// #include "../glad/include/glad/glad.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include "../ostalo/ostalo.h"
#include <map>
#include "../Scena/Scena.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../Matematika/Matematika.h"
class Render
{
public:
    Render();
    void Init(const std::string &ime);
    void Narisi(uint32_t tekstura, spl::vec3 poz, float rot, spl::vec3 vel, Barva BObj, Barva BOzd);
    void DodajSceno(Scena *scena, const std::string &ime);
    void AktivirajSceno(const std::string &ime);
    uint32_t NaloziTeksturo(const std::string &pot);
    void Zanka();
    bool AliSeMoramZapreti();
    void OkvirZac();
    void OkvirKon();
    Barva Odzadje;

private:
    Scena *m_aktivnaScena = NULL;
    std::map<std::string, Scena *> scene;
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