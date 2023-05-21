#include "Render.h"
#include "../ostalo/ostalo.h"
#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <ft2build.h>
#include FT_FREETYPE_H
void Render::DodajSceno(Scena *scena, const std::string &ime)
{
    scene.insert({ime, scena});
}
void Render::AktivirajSceno(const std::string &ime)
{
    if (m_aktivnaScena != NULL)
        m_aktivnaScena->Konec();
    auto najdeno = scene.find(ime);
    m_aktivnaScena = najdeno->second;
    m_aktivnaScena->Zacetek();
}
uint32_t Render::NaloziTeksturo(const std::string &pot)
{
    std::string dejpot = "../";
    dejpot += pot;
    uint32_t tekstura;

    glGenTextures(1, &tekstura);
    glBindTexture(GL_TEXTURE_2D, tekstura);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    int dolzina, visina, kanali;
    stbi_set_flip_vertically_on_load(1);
    unsigned char *data = stbi_load(dejpot.c_str(), &dolzina, &visina, &kanali, 0);
    // std::cout << kanali << std::endl;
    if (!data)
        io::izpis("NI TEKSTURE", io::type::error);
    else
    {
        switch (kanali)
        {
        case 4:
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, dolzina, visina, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            break;
        case 3:
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, dolzina, visina, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            break;
        }
    }
    stbi_image_free(data);
    return tekstura;
}
Render::Render()
    : Odzadje(0x000000ff), m_proj(1)
{
}
void Render::Init(const std::string &ime)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_okno = glfwCreateWindow(800, 600, ime.c_str(), NULL, NULL);

    if (m_okno == NULL)
    {
        glfwTerminate();
        io::izpis("NI USTVARILO OKNA", io::type::error);
    }

    glfwMakeContextCurrent(m_okno);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        glfwTerminate();
        io::izpis("NI USTVARILO GLAD-a", io::type::error);
    }
    glViewport(0, 0, 800, 600);

    glfwSetFramebufferSizeCallback(m_okno, PosodobiVelOkna);

    // glfwSwapInterval(0);

    NastaviShaderje();
    NastaviBuferje();

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    /*
        BindajStaticneBufferje();
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        BindajDinamicneBufferje();
        */
}
void Render::BindajStaticneBufferje()
{
    glBindVertexArray(m_SVAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_SVBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_SEBO);
}
void Render::BindajDinamicneBufferje()
{
    glBindVertexArray(m_DVAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_DVBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_DEBO);
}
bool Render::AliSeMoramZapreti()
{
    return glfwWindowShouldClose(m_okno);
}
void Render::OkvirKon()
{
    glfwPollEvents();
    glfwSwapBuffers(m_okno);
}
void Render::OkvirZac()
{
    DobiVhod();

    glClearColor(Odzadje.r, Odzadje.g, Odzadje.b, Odzadje.a);
    glClear(GL_COLOR_BUFFER_BIT);
}
void Render::Zanka()
{

    glfwGetWindowSize(m_okno, &okno.dolzina, &okno.visina);
    glfwGetCursorPos(m_okno, &kazalec.x, &kazalec.y);
    m_proj = glm::ortho(0.0f, (float)okno.dolzina, (float)okno.visina, 0.0f);

    m_aktivnaScena->Zanka();
}
void Render::Narisi(uint32_t tekstura, spl::vec3 poz, float rot, spl::vec3 vel, Barva obj, Barva ozd)
{
    glActiveTexture(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE0, tekstura);
    glUniform1i(glGetUniformLocation(m_shaderProgram, "tekID"), 0);

    glUniform4f(glGetUniformLocation(m_shaderProgram, "obj"), obj.r, obj.g, obj.b, obj.a);
    glUniform4f(glGetUniformLocation(m_shaderProgram, "ozd"), ozd.r, ozd.g, ozd.b, ozd.a);

    glUniformMatrix4fv(glGetUniformLocation(m_shaderProgram, "proj"), 1, GL_FALSE, &m_proj[0][0]);

    glm::mat4 matrika = glm::mat4(1);

    matrika = glm::translate(matrika, glm::vec3(poz.x, poz.y, 0));

    matrika = glm::scale(matrika, glm::vec3(vel.x, vel.y, 0));

    matrika = glm::rotate(matrika, glm::radians(rot), glm::vec3(0, 0, 1));
    glUniformMatrix4fv(glGetUniformLocation(m_shaderProgram, "matrika"), 1, GL_FALSE, &matrika[0][0]);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
void Render::NastaviShaderje()
{
    int uspeh;
    const char *vertexShaderSource = R"(
            #version 330 core
            layout (location = 0) in vec3 Vpos;
            layout (location = 1) in vec2 Tpos;
            out vec2 tpos;
            uniform mat4 matrika;
            uniform mat4 proj;
            void main()
            {
                gl_Position =proj * matrika  * vec4(Vpos,1.0);
                tpos=Tpos;
            }
        )";
    uint32_t vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &uspeh);
    if (!uspeh)
        io::izpis("NI VERTEX-SHADER PROGRAMA", io::type::error);

    const char *fragemntShaderSource = R"(
            #version 330 core

            out vec4 FragColor;
            uniform sampler2D tekID;
            uniform vec4 obj;
            uniform vec4 ozd;
            in vec2 tpos;
            void main()
            {
                vec4 slika=texture(tekID,tpos);
                if(slika.w<0.3)
                FragColor=ozd;
                else
                FragColor=slika*obj;
            }
        )";
    uint32_t fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragemntShaderSource, NULL);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &uspeh);
    if (!uspeh)
        io::izpis("NI FRAGMENT-SHADER PROGRAMA", io::type::error);
    m_shaderProgram = glCreateProgram();
    glAttachShader(m_shaderProgram, vertexShader);
    glAttachShader(m_shaderProgram, fragmentShader);
    glLinkProgram(m_shaderProgram);
    glGetProgramiv(m_shaderProgram, GL_LINK_STATUS, &uspeh);
    if (!uspeh)
        io::izpis("NI SHADER PROGRAMA", io::type::error);
    glUseProgram(m_shaderProgram);
    glDeleteShader(fragmentShader);
    glDeleteShader(vertexShader);
}
void Render::NastaviBuferje()
{
    //! staticni
    glGenVertexArrays(1, &m_SVAO);
    glBindVertexArray(m_SVAO);

    glGenBuffers(1, &m_SVBO);
    glBindBuffer(GL_ARRAY_BUFFER, m_SVBO);

    glGenBuffers(1, &m_SEBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_SEBO);

    float tocke[] =
        {
            -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
            1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
            1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
            -1.0f, 1.0f, 0.0f, 0.0f, 1.0f};
    uint32_t indeksi[] =
        {
            0, 1, 2,
            0, 2, 3};

    glBufferData(GL_ARRAY_BUFFER, sizeof(tocke), tocke, GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indeksi), indeksi, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    //! dinamicni
    glGenVertexArrays(1, &m_DVAO);
    glBindVertexArray(m_DVAO);

    glGenBuffers(1, &m_DVBO);
    glBindBuffer(GL_ARRAY_BUFFER, m_DVBO);

    glGenBuffers(1, &m_DEBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_DEBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(tocke), tocke, GL_DYNAMIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indeksi), indeksi, GL_DYNAMIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
}
void Render::PosodobiVelOkna(GLFWwindow *okno, int dolzina, int visina)
{
    glViewport(0, 0, dolzina, visina);
}
void Render::DobiVhod()
{
    if (glfwGetKey(m_okno, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(m_okno, GLFW_TRUE);
}