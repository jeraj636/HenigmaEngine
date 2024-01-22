#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "../include/log.h"
#include "../include/font.h"
#include "../include/zvok.h"

#include "../include/risalnik.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

double Cas::get_time()
{
    return glfwGetTime();
}

double Cas::get_delta_time()
{
    return m_delta_time;
}

void Risalnik::init(const std::string &naslov, const mat::vec2 &velikost)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_DECORATED, GL_FALSE);
    glfwWindowHint(GLFW_SCALE_TO_MONITOR, GL_TRUE);
    m_okno = glfwCreateWindow(1920, 1080, naslov.c_str(), NULL, NULL);

    if (m_okno == nullptr)
    {
        glfwTerminate();
        log::err("NI OKNA");
    }
    log::msg("OKNO DELUJE");

    glfwMakeContextCurrent(m_okno);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        log::err("NI GLADA");
    }
    log::msg("GLAD DELA");

    glViewport(0, 0, 1920, 1080);

    m_vel_okno = mat::vec2(1920, 1080);

    nalozi_klice_nazaj();

    nalozi_shaderje();
    nalozi_bufferje();

    nalozi_shaderje_b();
    nalozi_bufferje_b();

    nalozi_shaderje_p();
    nalozi_bufferje_p();

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glfwSwapInterval(0);

    m_miskin_gumb = Gumb::ni_pritisnjen;
    m_fps = 0;
    m_t_fps = 0;
}

bool Risalnik::ali_se_moram_zapreti()
{
    return glfwWindowShouldClose(m_okno);
}

void Risalnik::konec()
{
    glfwTerminate();
    log::msg("KONEC");
    exit(0);
}

uint32_t Risalnik::nalozi_teksturo(const std::string &pot_do_teksture)
{
    std::string pot = sredstva_pot;
    pot = pot + "/" + pot_do_teksture;

    uint32_t tekstura;

    glGenTextures(1, &tekstura);
    glBindTexture(GL_TEXTURE_2D, tekstura);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    int x, y, kanali;
    stbi_set_flip_vertically_on_load(1);

    unsigned char *data = stbi_load(pot.c_str(), &x, &y, &kanali, 4);

    if (!data)
    {
        log::war(pot.c_str());
        log::err("NI SLIKE");
    }
    else
    {
        log::msg("SLIKA DELUJE");
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, x, y, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    }
    stbi_image_free(data);
    return tekstura;
}

Font Risalnik::nalozi_font(const std::string &pot_do_pisave, uint32_t velikost)
{
    std::string prava_pot = sredstva_pot;
    prava_pot = prava_pot + "/" + pot_do_pisave;
    return Font(prava_pot, velikost);
}
Zvok Risalnik::nalozi_zvok(const std::string &pot_do_zvoka)
{
    Zvok t;
    std::string prava_pot = sredstva_pot;
    prava_pot = prava_pot + "/" + pot_do_zvoka;
    t.nastavi(prava_pot);
    return t;
}
void Risalnik::narisi(uint32_t tekstura_id, const Barva &b_obj, const Barva &b_ozd, const mat::vec2 poz, float rot, const mat::vec2 vel)
{
    glBindVertexArray(m_VAO);

    glUseProgram(m_shader_program);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, tekstura_id);

    mat::mat::mat3 pozicijska(1);
    mat::mat::Premik(poz, pozicijska);
    mat::mat::mat3 velikostna(1);
    mat::mat::velikostna(vel, velikostna);
    mat::mat::mat3 vrtilna(1);
    mat::mat::Vrtilna(mat::rad(rot), vrtilna);

    glUniformMatrix3fv(glGetUniformLocation(m_shader_program, "u_rotacija"), 1, GL_TRUE, &vrtilna.m_mat[0][0]);
    glUniformMatrix3fv(glGetUniformLocation(m_shader_program, "u_velikost"), 1, GL_TRUE, &velikostna.m_mat[0][0]);
    glUniformMatrix3fv(glGetUniformLocation(m_shader_program, "u_premik"), 1, GL_TRUE, &pozicijska.m_mat[0][0]);
    glUniformMatrix3fv(glGetUniformLocation(m_shader_program, "u_orto"), 1, GL_TRUE, &m_orto.m_mat[0][0]);

    glUniform4f(glGetUniformLocation(m_shader_program, "u_b_obj"), b_obj.get_r(), b_obj.get_g(), b_obj.get_b(), b_obj.get_a());
    glUniform4f(glGetUniformLocation(m_shader_program, "u_b_ozd"), b_ozd.get_r(), b_ozd.get_g(), b_ozd.get_b(), b_ozd.get_a());
    glUniform1i(glGetUniformLocation(m_shader_program, "u_tek_id"), 0);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
    glUseProgram(0);
}

void Risalnik::narisi_niz(const Font &font, const Barva &b_obj, const Barva b_ozd, mat::vec2 poz, float vel, const std::string &niz)
{

    float *tocke = new float[16 * niz.size()];
    uint32_t *indeksi = new uint32_t[6 * niz.size()];

    stbtt_aligned_quad quad;
    poz.x /= (Risalnik::get_velikost_okna().x / 2);
    poz.y /= (Risalnik::get_velikost_okna().y / 2);
    poz.x -= 1;
    poz.y -= 1;

    float x = 0.0f, y = 0.0f;
    for (int i = 0; i < niz.size(); i++)
    {
        stbtt_GetBakedQuad(font.char_data, 512, 512, niz[i], &x, &y, &quad, false);

        quad.x0 /= vel;
        quad.x1 /= vel;
        quad.y0 /= -vel;
        quad.y1 /= -vel;

        tocke[i * 16 + 0] = quad.x0 + poz.x;
        tocke[i * 16 + 1] = quad.y0 + poz.y;
        tocke[i * 16 + 2] = quad.s0;
        tocke[i * 16 + 3] = quad.t0;

        tocke[i * 16 + 4] = quad.x1 + poz.x;
        tocke[i * 16 + 5] = quad.y0 + poz.y;
        tocke[i * 16 + 6] = quad.s1;
        tocke[i * 16 + 7] = quad.t0;

        tocke[i * 16 + 8] = quad.x1 + poz.x;
        tocke[i * 16 + 9] = quad.y1 + poz.y;
        tocke[i * 16 + 10] = quad.s1;
        tocke[i * 16 + 11] = quad.t1;

        tocke[i * 16 + 12] = quad.x0 + poz.x;
        tocke[i * 16 + 13] = quad.y1 + poz.y;
        tocke[i * 16 + 14] = quad.s0;
        tocke[i * 16 + 15] = quad.t1;

        indeksi[i * 6 + 0] = 0 + i * 4;
        indeksi[i * 6 + 1] = 1 + i * 4;
        indeksi[i * 6 + 2] = 2 + i * 4;
        indeksi[i * 6 + 3] = 0 + i * 4;
        indeksi[i * 6 + 4] = 2 + i * 4;
        indeksi[i * 6 + 5] = 3 + i * 4;
        x += quad.x1 - quad.x0;
    }

    glBindVertexArray(m_VAO_b);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO_b);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO_b);
    glUseProgram(m_shader_program_b);

    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float) * 16 * niz.size(), tocke);
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, sizeof(uint32_t) * 6 * niz.size(), indeksi);

    glActiveTexture(GL_TEXTURE0);

    glBindTexture(GL_TEXTURE_2D, font.tekstura);

    glUniform4f(glGetUniformLocation(m_shader_program_b, "u_b_obj"), b_obj.get_r(), b_obj.get_g(), b_obj.get_b(), b_obj.get_a());
    glUniform4f(glGetUniformLocation(m_shader_program_b, "u_b_ozd"), b_ozd.get_r(), b_ozd.get_g(), b_ozd.get_b(), b_ozd.get_a());
    glUniform1i(glGetUniformLocation(m_shader_program_b, "u_tek_id"), 0);

    glDrawElements(GL_TRIANGLES, 6 * niz.size(), GL_UNSIGNED_INT, 0);

    glBindVertexArray(0);
    glUseProgram(0);

    delete[] tocke;
    delete[] indeksi;
}

void Risalnik::narisi_niz(const Font &font, const Barva &b_obj, const Barva b_ozd, float poz_y, float vel, const std::string &niz)
{

    float *tocke = new float[16 * niz.size()];
    uint32_t *indeksi = new uint32_t[6 * niz.size()];

    stbtt_aligned_quad quad;

    poz_y /= (Risalnik::get_velikost_okna().y / 2);
    poz_y -= 1;

    float x = 0.0f, y = 0.0f;

    float poz_x = 0;
    for (int i = 0; i < niz.size(); i++)
    {
        stbtt_GetBakedQuad(font.char_data, 512, 512, niz[i], &x, &y, &quad, false);
    }
    x /= Risalnik::get_velikost_okna().x;
    poz_x = -x * 2;
    x = 0.0f;
    y = 0.0f;
    for (int i = 0; i < niz.size(); i++)
    {
        stbtt_GetBakedQuad(font.char_data, 512, 512, niz[i], &x, &y, &quad, false);

        quad.x0 /= vel;
        quad.x1 /= vel;
        quad.y0 /= -vel;
        quad.y1 /= -vel;

        tocke[i * 16 + 0] = quad.x0 + poz_x;
        tocke[i * 16 + 1] = quad.y0 + poz_y;
        tocke[i * 16 + 2] = quad.s0;
        tocke[i * 16 + 3] = quad.t0;

        tocke[i * 16 + 4] = quad.x1 + poz_x;
        tocke[i * 16 + 5] = quad.y0 + poz_y;
        tocke[i * 16 + 6] = quad.s1;
        tocke[i * 16 + 7] = quad.t0;

        tocke[i * 16 + 8] = quad.x1 + poz_x;
        tocke[i * 16 + 9] = quad.y1 + poz_y;
        tocke[i * 16 + 10] = quad.s1;
        tocke[i * 16 + 11] = quad.t1;

        tocke[i * 16 + 12] = quad.x0 + poz_x;
        tocke[i * 16 + 13] = quad.y1 + poz_y;
        tocke[i * 16 + 14] = quad.s0;
        tocke[i * 16 + 15] = quad.t1;

        indeksi[i * 6 + 0] = 0 + i * 4;
        indeksi[i * 6 + 1] = 1 + i * 4;
        indeksi[i * 6 + 2] = 2 + i * 4;
        indeksi[i * 6 + 3] = 0 + i * 4;
        indeksi[i * 6 + 4] = 2 + i * 4;
        indeksi[i * 6 + 5] = 3 + i * 4;
        x += quad.x1 - quad.x0;
    }

    glBindVertexArray(m_VAO_b);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO_b);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO_b);
    glUseProgram(m_shader_program_b);

    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float) * 16 * niz.size(), tocke);
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, sizeof(uint32_t) * 6 * niz.size(), indeksi);

    glActiveTexture(GL_TEXTURE0);

    glBindTexture(GL_TEXTURE_2D, font.tekstura);

    glUniform4f(glGetUniformLocation(m_shader_program_b, "u_b_obj"), b_obj.get_r(), b_obj.get_g(), b_obj.get_b(), b_obj.get_a());
    glUniform4f(glGetUniformLocation(m_shader_program_b, "u_b_ozd"), b_ozd.get_r(), b_ozd.get_g(), b_ozd.get_b(), b_ozd.get_a());
    glUniform1i(glGetUniformLocation(m_shader_program_b, "u_tek_id"), 0);

    glDrawElements(GL_TRIANGLES, 6 * niz.size(), GL_UNSIGNED_INT, 0);

    glBindVertexArray(0);
    glUseProgram(0);

    delete[] tocke;
    delete[] indeksi;
}
void Risalnik::narisi_ploscice(uint32_t tekstura_id, const Barva &b_obj, float *tocke, uint32_t *indeksi, int n)
{

    glBindVertexArray(m_VAO_p);

    glBindBuffer(GL_ARRAY_BUFFER, m_VBO_p);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO_p);

    glUseProgram(m_shader_program_p);

    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float) * 16 * n, tocke);
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, sizeof(uint32_t) * 6 * n, indeksi);

    glActiveTexture(GL_TEXTURE0);

    glBindTexture(GL_TEXTURE_2D, tekstura_id);

    glUniform4f(glGetUniformLocation(m_shader_program_p, "u_b_obj"), b_obj.get_r(), b_obj.get_g(), b_obj.get_b(), b_obj.get_a());
    glUniform1i(glGetUniformLocation(m_shader_program_p, "u_tek_id"), 0);
    glUniformMatrix3fv(glGetUniformLocation(m_shader_program_p, "u_orto"), 1, GL_TRUE, &Risalnik::get_orto().m_mat[0][0]);

    glDrawElements(GL_TRIANGLES, 6 * n, GL_UNSIGNED_INT, 0);
    // std::cout << n << "\n";
    glBindVertexArray(0);
    glUseProgram(0);
}
void Risalnik::zacetek_okvir()
{
    glClearColor(barva_odzadja.get_r(), barva_odzadja.get_g(), barva_odzadja.get_b(), barva_odzadja.get_a());
    glClear(GL_COLOR_BUFFER_BIT);

    int x, y;
    glfwGetWindowSize(m_okno, &x, &y);

    m_vel_okno = mat::vec2((float)x, (float)y);
    m_orto = mat::mat::mat3(1);
    mat::mat::Orto(.0f, (float)m_vel_okno.x, .0f, (float)m_vel_okno.y, m_orto);

    double dx, dy;
    glfwGetCursorPos(m_okno, &dx, &dy);

    m_poz_kazalca = mat::vec2((float)dx, (float)dy);

    Cas::m_zac_time = glfwGetTime();

    if (m_naslednji_fsp_cas <= glfwGetTime())
    {
        m_naslednji_fsp_cas += 1;
        m_fps = m_t_fps;
        m_t_fps = 0;
    }
    m_t_fps++;
}

void Risalnik::konec_okvir()
{
    glfwPollEvents();
    glfwSwapBuffers(m_okno);
    Cas::m_delta_time = glfwGetTime() - Cas::m_zac_time;
    if (Cas::m_delta_time < 1 / 15)
        Cas::m_delta_time = 1 / 15;
}

const mat::vec2 &Risalnik::get_poz_kazalca()
{
    return m_poz_kazalca;
}

const mat::mat::mat3 &Risalnik::get_orto()
{
    return m_orto;
}

const mat::vec2 &Risalnik::get_velikost_okna()
{
    return m_vel_okno;
}

const Gumb Risalnik::get_miskin_gumb()
{
    return m_miskin_gumb;
}

const uint32_t Risalnik::get_fps()
{
    return m_fps;
}

void Risalnik::velikost_okna_klic_nazaj(GLFWwindow *okno, int dolzina, int visina)
{
    glViewport(0, 0, dolzina, visina);
}

void Risalnik::gumb_klic_nazaj(GLFWwindow *okno, int kljuc, int koda_pritiska, int akcija, int mods)
{
    if (kljuc < 0 || kljuc > 128)
        return;
    if (akcija == GLFW_PRESS)
        m_tipke[kljuc] = true;
    if (akcija == GLFW_RELEASE)
        m_tipke[kljuc] = false;
}

void Risalnik::miskin_gumb_klic_nazaj(GLFWwindow *okno, int kljuc, int akcija, int mods)
{
    if (kljuc == GLFW_MOUSE_BUTTON_LEFT && akcija == GLFW_PRESS)
        m_miskin_gumb = Gumb::levi;
    else if (kljuc == GLFW_MOUSE_BUTTON_RIGHT && akcija == GLFW_PRESS)
        m_miskin_gumb = Gumb::desni;
    else
        m_miskin_gumb = Gumb::ni_pritisnjen;
}

void Risalnik::nalozi_klice_nazaj()
{
    glfwSetFramebufferSizeCallback(m_okno, velikost_okna_klic_nazaj);
    glfwSetKeyCallback(m_okno, gumb_klic_nazaj);
    glfwSetMouseButtonCallback(m_okno, miskin_gumb_klic_nazaj);
}

void Risalnik::nalozi_shaderje()
{
    const char *vertex_shader_source = R"(
        #version 330 core
        layout (location = 0) in vec2 a_poz;
        layout (location = 1) in vec2 i_tek_poz;

        uniform mat3 u_rotacija;
        uniform mat3 u_velikost;
        uniform mat3 u_premik;
        uniform mat3 u_orto;

        out vec2 tek_poz;

        void main()
        {
            gl_Position = vec4(u_orto * (u_premik * (u_rotacija * (u_velikost * vec3(a_poz,1.0f)))),1.0f);
            tek_poz = i_tek_poz;
        }

    )";
    const char *fragment_shader_source = R"(
        #version 330 core
        in vec2 tek_poz;

        uniform vec4 u_b_obj;
        uniform vec4 u_b_ozd;

        uniform sampler2D u_tek_id;
        out vec4 frag_color;
        void main()
        {
            vec4 tekstura = texture(u_tek_id,tek_poz);
            frag_color = tekstura * u_b_obj;
        }
    )";

    uint32_t vertex_shader;
    uint32_t fragment_shader;

    int uspeh;

    vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertex_shader_source, NULL);
    glCompileShader(vertex_shader);

    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &uspeh);

    if (!uspeh)
    {
        char info_log[512];
        glGetShaderInfoLog(vertex_shader, 512, NULL, info_log);
        std::cout << info_log << "\n";
        log::err("NI VERTEX SHADERJA");
    }
    log::msg("VERTEX SHADER");

    fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragment_shader_source, NULL);
    glCompileShader(fragment_shader);

    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &uspeh);

    if (!uspeh)
    {
        char info_log[512];
        glGetShaderInfoLog(fragment_shader, 512, NULL, info_log);
        std::cout << info_log << "\n";
        log::err("NI FRAGMENT SHADERJA");
    }
    log::msg("FRAGMENT SHADER");

    m_shader_program = glCreateProgram();

    glAttachShader(m_shader_program, vertex_shader);
    glAttachShader(m_shader_program, fragment_shader);

    glLinkProgram(m_shader_program);

    glGetProgramiv(m_shader_program, GL_LINK_STATUS, &uspeh);
    if (!uspeh)
    {
        char info_log[512];
        glGetProgramInfoLog(m_shader_program, 512, NULL, info_log);
        std::cout << info_log << std::endl;
        log::err("NI SHADER PROGARMA");
    }
    glUseProgram(m_shader_program);
    log::msg("SHADER PROGRAM");
    glDeleteShader(fragment_shader);
    glDeleteShader(vertex_shader);

    glUseProgram(0);
}

void Risalnik::nalozi_shaderje_b()
{
    const char *vertex_shader_source = R"(
        #version 330 core
        layout (location = 0) in vec2 a_poz;
        layout (location = 1) in vec2 i_tek_poz;

  

        out vec2 tek_poz;

        void main()
        {
            gl_Position = vec4(a_poz,1.0,1.0);
            tek_poz = i_tek_poz;
        }

    )";
    const char *fragment_shader_source = R"(
        #version 330 core
        in vec2 tek_poz;

        uniform vec4 u_b_obj;
        uniform vec4 u_b_ozd;

        uniform sampler2D u_tek_id;
        out vec4 frag_color;
        void main()
        {
            vec4 tekstura = texture(u_tek_id,tek_poz);
            frag_color = tekstura.r * u_b_obj;
        }
    )";

    uint32_t vertex_shader;
    uint32_t fragment_shader;

    int uspeh;

    vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertex_shader_source, NULL);
    glCompileShader(vertex_shader);

    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &uspeh);

    if (!uspeh)
    {
        char info_log[512];
        glGetShaderInfoLog(vertex_shader, 512, NULL, info_log);
        std::cout << info_log << std::endl;
        log::err("NI VERTEX SHADERJA B");
    }
    log::msg("VERTEX SHADER B");

    fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragment_shader_source, NULL);
    glCompileShader(fragment_shader);

    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &uspeh);

    if (!uspeh)
    {
        char info_log[512];
        glGetShaderInfoLog(fragment_shader, 512, NULL, info_log);
        std::cout << info_log << std::endl;
        log::err("NI FRAGMENT SHADERJA B");
    }
    log::msg("FRAGMENT SHADER B");

    m_shader_program_b = glCreateProgram();
    glAttachShader(m_shader_program_b, vertex_shader);
    glAttachShader(m_shader_program_b, fragment_shader);
    glLinkProgram(m_shader_program_b);

    glGetProgramiv(m_shader_program_b, GL_LINK_STATUS, &uspeh);
    if (!uspeh)
    {
        char info_log[512];
        glGetProgramInfoLog(m_shader_program_b, 512, NULL, info_log);
        std::cout << info_log << std::endl;
        log::err("NI SHADER PROGARMA B");
    }
    log::msg("SHADER PROGARM B");

    glDeleteShader(fragment_shader);
    glDeleteShader(vertex_shader);
}

void Risalnik::nalozi_shaderje_p()
{
    const char *vertex_shader_source = R"(
        #version 330 core
        layout (location = 0) in vec2 a_poz;
        layout (location = 1) in vec2 i_tek_poz;

        uniform mat3 u_orto;

        out vec2 tek_poz;

        void main()
        {
            gl_Position = vec4(u_orto * vec3(a_poz,1.0),1.0);
            tek_poz = i_tek_poz;
        }

    )";
    const char *fragment_shader_source = R"(
        #version 330 core
        in vec2 tek_poz;

        uniform vec4 u_b_obj;

        uniform sampler2D u_tek_id;
        out vec4 frag_color;
        void main()
        {
            vec4 tekstura = texture(u_tek_id,tek_poz);
            frag_color = tekstura.r * u_b_obj;
        }
    )";

    uint32_t vertex_shader;
    uint32_t fragment_shader;

    int uspeh;

    vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertex_shader_source, NULL);
    glCompileShader(vertex_shader);

    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &uspeh);

    if (!uspeh)
    {
        char info_log[512];
        glGetShaderInfoLog(vertex_shader, 512, NULL, info_log);
        std::cout << info_log << std::endl;
        log::err("NI VERTEX SHADERJA P");
    }
    log::msg("VERTEX SHADER P");

    fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragment_shader_source, NULL);
    glCompileShader(fragment_shader);

    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &uspeh);

    if (!uspeh)
    {
        char info_log[512];
        glGetShaderInfoLog(fragment_shader, 512, NULL, info_log);
        std::cout << info_log << std::endl;
        log::err("NI FRAGMENT SHADERJA P");
    }
    log::msg("FRAGMENT SHADER P");

    m_shader_program_p = glCreateProgram();
    glAttachShader(m_shader_program_p, vertex_shader);
    glAttachShader(m_shader_program_p, fragment_shader);
    glLinkProgram(m_shader_program_p);

    glGetProgramiv(m_shader_program_p, GL_LINK_STATUS, &uspeh);
    if (!uspeh)
    {
        char info_log[512];
        glGetProgramInfoLog(m_shader_program_p, 512, NULL, info_log);
        std::cout << info_log << std::endl;
        log::err("NI SHADER PROGARMA P");
    }
    log::msg("SHADER PROGARM P");

    glDeleteShader(fragment_shader);
    glDeleteShader(vertex_shader);
}
void Risalnik::nalozi_bufferje()
{
    float tocke[] =
        {
            -.5f, -.5f, .0f, .0f,
            .5f, -.5f, 1.0f, 0.0f,
            .5f, .5f, 1.0f, 1.0f,
            -.5f, .5f, .0f, 1.0f};
    uint32_t indeksi[]{
        0, 1, 2,
        0, 2, 3};

    glGenVertexArrays(1, &m_VAO);
    glBindVertexArray(m_VAO);

    glGenBuffers(1, &m_VBO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(tocke), tocke, GL_STATIC_DRAW);

    glGenBuffers(1, &m_EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indeksi), indeksi, GL_STATIC_DRAW);

    glUseProgram(m_shader_program);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glUseProgram(0);
}

void Risalnik::nalozi_bufferje_b()
{

    glGenVertexArrays(1, &m_VAO_b);
    glBindVertexArray(m_VAO_b);

    glGenBuffers(1, &m_VBO_b);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO_b);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 100 * 16, nullptr, GL_DYNAMIC_DRAW);

    glGenBuffers(1, &m_EBO_b);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO_b);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32_t) * 100 * 6, nullptr, GL_DYNAMIC_DRAW);

    glUseProgram(m_shader_program_b);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glUseProgram(0);
}

void Risalnik::nalozi_bufferje_p()
{

    glGenVertexArrays(1, &m_VAO_p);
    glBindVertexArray(m_VAO_p);

    glGenBuffers(1, &m_VBO_p);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO_p);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6000 * 16, nullptr, GL_DYNAMIC_DRAW);

    glGenBuffers(1, &m_EBO_p);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO_p);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32_t) * 6000 * 6, nullptr, GL_DYNAMIC_DRAW);

    glUseProgram(m_shader_program_p);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glUseProgram(0);
}