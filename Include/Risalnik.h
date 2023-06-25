#ifndef RISALNIK_H
#define RISALNIK_H

#include <stdint.h>
#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Barva.h"
#include "Matematika.h"

struct GLFWwindow;
class Font;
class Znak;

class Risalnik
{
public:
    static void Init(const char *naslov);
    static void Zanka();
    static bool AliSeMoramZapreti();
    static void Narisi(uint32_t tekID, Barva Bobj, Barva Bozd, vec3 poz, float rot, vec3 vel);
    static void NarisiZnak(Znak znak, Barva Bobj, Barva Bozd, vec3 poz, float rot, float vel);
    static uint32_t NaloziTeksturo(std::string potDoSlike);
    static void ZacetekFrame();
    static void KonecFrame();
    static Font NaloziFont(std::string potDoFonta, int velikost);

public:
    inline static std::string sredstvaPath;
    inline static Barva odzadje;

private:
    static void VelikostOknaCallBack(GLFWwindow *okno, int dolzina, int visina);
    static void GumbCallBack(GLFWwindow *okno, int key, int scanCode, int akcija, int mods);
    static void NaloziCallBack();
    // static void GumbMiskeCallBack();
    // static void CharCallBack();

    static void NaloziBufferje();
    static void NaloziBufferjeB();

    static void NarediShaderje();
    static void NarediShaderjeB();
    static void OdpriOkno(const char *naslov);

private:
    inline static GLFWwindow *m_okno;

    inline static glm::mat4 m_orto;

    inline static uint32_t m_VBO;
    inline static uint32_t m_VAO;
    inline static uint32_t m_EBO;

    inline static uint32_t m_shaderProgram;
    inline static uint32_t m_vertexShader;
    inline static uint32_t m_fragmentShader;

    inline static uint32_t m_EBOB;
    inline static uint32_t m_VAOB;
    inline static uint32_t m_VBOB;

    inline static uint32_t m_shaderProgramB;
    inline static uint32_t m_vertexShaderB;
    inline static uint32_t m_fragmentShaderB;

    inline static vec2 m_velOkna;
    inline static vec2 m_pozKazalca;
};
#endif