#ifndef RISALNIK_H
#define RISALNIK_H

#include <stdint.h>
#include <string>

#include <matematika/matematika.h>

#include "barva.h"
struct GLFWwindow;

class Font;
class Scena;
class Zvok;
// class Znak;
//  class Objekt;
//   class Glasba;
//    class Ploscice;
class Risalnik;

class Cas
{
public:
    static double get_time();
    static double get_delta_time();
    friend class Risalnik;

protected:
    static inline double m_zac_time;
    static inline double m_delta_time;
};
enum class Gumb
{
    levi,
    desni,
    ni_pritisnjen
};
class Risalnik
{
public:
    static void init(const std::string &naslov, const mat::vec2 &velikost);
    static bool ali_se_moram_zapreti();
    static void konec();

    static uint32_t nalozi_teksturo(const std::string &pot_do_teksture);
    static Font nalozi_font(const std::string &pot_do_pisave, uint32_t velikost);
    static Zvok nalozi_zvok(const std::string &pot_do_zvoka);
    static void skenslaj_teksturo(uint32_t *tekstura_id);

    static void narisi(uint32_t tekstura_id, const Barva &b_obj, const Barva &b_ozd, const mat::vec2 poz, float rot, const mat::vec2 vel);
    static void narisi_niz(const Font &font, const Barva &b_obj, const Barva b_ozd, mat::vec2 poz, float vel, const std::string &niz);
    static void narisi_niz(const Font &font, const Barva &b_obj, const Barva b_ozd, float poz_y, float vel, const std::string &niz);
    static void narisi_ploscice(uint32_t tekstura_id, const Barva &b_obj, float *tocke, uint32_t *indeksi, int n);
    // static void narisi_vec_objektov();

    static void zacetek_okvir();
    static void konec_okvir();

    static const mat::vec2 &get_poz_kazalca();
    static const mat::mat::mat3 &get_orto();
    static const mat::vec2 &get_velikost_okna();
    static const Gumb get_miskin_gumb();
    static const uint32_t get_fps();

public:
    inline static std::string sredstva_pot;
    inline static Barva barva_odzadja;
    inline static Scena *aktivna_scena;

private:
    static void velikost_okna_klic_nazaj(GLFWwindow *okno, int dolzina, int visina);
    static void gumb_klic_nazaj(GLFWwindow *okno, int kljuc, int koda_pritiska, int akcija, int mods);
    static void miskin_gumb_klic_nazaj(GLFWwindow *okno, int kljuc, int akcija, int mods);
    static void nalozi_klice_nazaj();

    static void nalozi_shaderje();
    static void nalozi_bufferje();

    static void nalozi_shaderje_b();
    static void nalozi_bufferje_b();

    static void nalozi_shaderje_p();
    static void nalozi_bufferje_p();

private:
    inline static GLFWwindow *m_okno;

    inline static uint32_t m_shader_program;
    inline static uint32_t m_shader_program_p;
    inline static uint32_t m_shader_program_b;

    inline static uint32_t m_VAO;
    inline static uint32_t m_VBO;
    inline static uint32_t m_EBO;

    inline static uint32_t m_VAO_b;
    inline static uint32_t m_VBO_b;
    inline static uint32_t m_EBO_b;

    inline static uint32_t m_VAO_p;
    inline static uint32_t m_VBO_p;
    inline static uint32_t m_EBO_p;

    inline static mat::vec2 m_poz_kazalca;
    inline static Gumb m_miskin_gumb;
    inline static bool m_tipke[128];
    inline static mat::mat::mat3 m_orto;
    inline static mat::vec2 m_vel_okno;

    inline static uint32_t m_t_fps;
    inline static uint32_t m_fps;
    inline static double m_naslednji_fsp_cas;
};
#endif
