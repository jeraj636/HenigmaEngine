#include "Render.h"
#include "../ostalo/ostalo.h"
#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

uint32_t Render::NaloziTeksturo(const std::string &pot)
{
    // dej je okrajsava ua dejanska
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
        spl::io::err("NI TEKSTURE");
    else
    {
        spl::io::msg("TEKSTURA DELUJE");
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
        spl::io::err("NI OKNA");
    }
    spl::io::msg("OKNO DELUJE");

    glfwMakeContextCurrent(m_okno);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        glfwTerminate();
        spl::io::err("NI GLADA");
    }
    spl::io::msg("GLAD DELUJE");

    glViewport(0, 0, 800, 600);

    glfwSetFramebufferSizeCallback(m_okno, PosodobiVelOkna);

    NastaviShaderje();
    NastaviBuferje();

    glfwSwapInterval(0);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}
void Render::BindajStaticneBufferje()
{
    glBindVertexArray(m_SVAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_SVBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_SEBO);
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

void Render::NastaviShaderje()
{
    //! navadni shaderjji
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
        spl::io::err("NI VERTEX SHADER-ja");
    spl::io::msg("DELUJE VERTEX SHADER");
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
        spl::io::err("NI FRAGMENT- SHADER PROGRAMA");
    spl::io::msg("DELA FRAGMENT SHADER");
    m_shaderProgram = glCreateProgram();
    glAttachShader(m_shaderProgram, vertexShader);
    glAttachShader(m_shaderProgram, fragmentShader);
    glLinkProgram(m_shaderProgram);
    glGetProgramiv(m_shaderProgram, GL_LINK_STATUS, &uspeh);
    if (!uspeh)
        spl::io::err("NI SHADER PROGRAMA");
    spl::io::msg("SHADER PROGRAM DELUJE");
    glUseProgram(m_shaderProgram);
    glDeleteShader(fragmentShader);
    glDeleteShader(vertexShader);

    //! shaderji za besedilo

    const char *vertexShaderSourceBes = R"(
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

    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSourceBes, NULL);
    glCompileShader(vertexShader);
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &uspeh);
    if (!uspeh)
        spl::io::err("NI BESEDILNEGA VERTEX SHADERJA");
    spl::io::msg("DELA BESEDILNI VERTEX SHADER");

    const char *fragmentShaderSourceBes = R"(
        #version 330 core
        in vec2 tpos;
        out vec4 color;

        uniform sampler2D TekID;
        uniform vec4 textColor;
        uniform vec4 ozdColor;

        void main()
        {
            vec4 tek=texture(TekID,tpos);
            if(tek.r<0.3f)
                color=ozdColor;
            else 
                color=vec4(tek.r,tek.r,tek.r,1)*textColor;
        }
    )";
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSourceBes, NULL);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &uspeh);
    if (!uspeh)
        spl::io::err("NI BESEDILNEGA FRAGMENT SHADERJA");
    spl::io::msg("BESEDILNI FRAGMENT SHADER");
    m_shaderProgramBes = glCreateProgram();
    glAttachShader(m_shaderProgramBes, vertexShader);
    glAttachShader(m_shaderProgramBes, fragmentShader);
    glLinkProgram(m_shaderProgramBes);
    glGetProgramiv(m_shaderProgramBes, GL_LINK_STATUS, &uspeh);
    if (!uspeh)
        spl::io::err("NI BESEDILNEGA PROGRAMA");
    spl::io::msg("BESDILNI SHADER PROGRAM");
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
    glUseProgram(m_shaderProgram);

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
