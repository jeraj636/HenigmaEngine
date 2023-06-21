#include "../../Include/Risalnik.h"
#include "../../Include/Log.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "STBImage.h"

void Risalnik::Init(const char *naslov)
{
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_okno = glfwCreateWindow(800, 600, naslov, NULL, NULL);

    if (m_okno == nullptr)
    {
        glfwTerminate();
        io::err("NI OKNA");
    }
    io::msg("OKNO DELUJE");

    glfwMakeContextCurrent(m_okno);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        glfwTerminate();
        io::err("NI GLADA");
    }
    io::msg("GLAD DELUJE");

    glViewport(0, 0, 800, 600);

    glfwSetFramebufferSizeCallback(m_okno, VelikostOknaCallBack);
    glfwSetKeyCallback(m_okno, GumbCallBack);
    NarediShaderje();
    NaloziBufferje();

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    // glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);

    glfwSwapInterval(0);
}

void Risalnik::ZacetekFrame()
{
    glClearColor(odzadje.r, odzadje.g, odzadje.b, odzadje.a);
    glClear(GL_COLOR_BUFFER_BIT);
    double x, y;
    glfwGetCursorPos(m_okno, &x, &y);
    m_pozKazalca.x = x;
    m_pozKazalca.y = y;
    int x1, y1;
    glfwGetWindowSize(m_okno, &x1, &y1);
    m_velOkna.x = x1;
    m_velOkna.y = y1;

    m_orto = glm::ortho(0.0f, (float)m_velOkna.x, (float)m_velOkna.y, 0.0f);
}

void Risalnik::KonecFrame()
{
    glfwPollEvents();
    glfwSwapBuffers(m_okno);
}

bool Risalnik::AliSeMoramZapreti()
{
    return glfwWindowShouldClose(m_okno);
}
void Risalnik::VelikostOknaCallBack(GLFWwindow *okno, int dolzina, int visina)
{
    glViewport(0, 0, dolzina, visina);
}
void Risalnik::NaloziBufferje()
{
    float tocke[20] =
        {
            -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
            0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
            0.5f, 0.5f, 0.0f, 1.0f, 1.0f,
            -0.5f, 0.5f, 0.0f, 0.0f, 1.0f};

    uint32_t indeksi[6] =
        {
            0, 1, 2,
            0, 2, 3};
    //* Ustvaritev VAO
    glGenVertexArrays(1, &m_VAO);
    glBindVertexArray(m_VAO);

    //* Ustvaritev VBO
    glGenBuffers(1, &m_VBO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 5 * 4, tocke, GL_STATIC_DRAW);

    //* Ustvaritev EBO
    glGenBuffers(1, &m_EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32_t) * 6, indeksi, GL_STATIC_DRAW);

    glUseProgram(m_shaderProgram);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
}

void Risalnik::NarediShaderje()
{
    const char *vertexShaderSRC = R"(
    #version 330 core
    layout (location = 0) in vec3 aPos;
    layout (location = 1) in vec2 aTekPos;

    out vec2 iTekPos;

    uniform mat4 uOrto;
    uniform mat4 uTrans;


    void main()
    {
        gl_Position = uOrto * uTrans * vec4(aPos.x, aPos.y, aPos.z , 1.0f);
        iTekPos = aTekPos;
    }

    )";

    const char *fragmentShaderSRC = R"(
        #version 330  core

        in vec2 iTekPos;

        uniform vec4 uBozd;
        uniform vec4 uBobj;
        uniform sampler2D uTekID;

        out vec4 FragColor;

        void main()
        {
            vec4 tekColor = texture(uTekID,iTekPos);
            vec4 barva = tekColor * uBobj;
            if(barva.w>0.5)
            FragColor=barva;
            else
            FragColor=uBozd;
        }
    )";

    m_vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(m_vertexShader, 1, &vertexShaderSRC, NULL);
    glCompileShader(m_vertexShader);

    int uspeh;
    glGetShaderiv(m_vertexShader, GL_COMPILE_STATUS, &uspeh);

    if (!uspeh)
    {
        char infoLog[512];
        glGetShaderInfoLog(m_vertexShader, 512, NULL, infoLog);
        std::cout << infoLog;
        io::err("NI VERTEX SHADERJA");
    }
    io::msg("DELUJE VERTEX SHADER");

    m_fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(m_fragmentShader, 1, &fragmentShaderSRC, NULL);
    glCompileShader(m_fragmentShader);

    glGetShaderiv(m_fragmentShader, GL_COMPILE_STATUS, &uspeh);

    if (!uspeh)
    {
        char infoLog[512];
        glGetShaderInfoLog(m_fragmentShader, 512, NULL, infoLog);
        std::cout << infoLog;
        io::err("NI FRAGMENT SHADERJA");
    }
    io::msg("DELUJE FRAGMENT SHADER");

    m_shaderProgram = glCreateProgram();
    glAttachShader(m_shaderProgram, m_vertexShader);
    glAttachShader(m_shaderProgram, m_fragmentShader);
    glLinkProgram(m_shaderProgram);
    glGetProgramiv(m_shaderProgram, GL_LINK_STATUS, &uspeh);

    if (!uspeh)
        io::err("NI SHADER PROGRAMA");
    io::msg("SHADER PROGRAM DELUJE");

    glUseProgram(m_shaderProgram);
    glDeleteShader(m_vertexShader);
    glDeleteShader(m_fragmentShader);
}
void Risalnik::Narisi(uint32_t tekID, Barva Bobj, Barva Bozd, vec3 poz, float rot, vec3 vel)
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, tekID);

    //* fragment shder
    glUniform4f(glGetUniformLocation(m_shaderProgram, "uBobj"), Bobj.r, Bobj.g, Bobj.b, Bobj.a);
    glUniform4f(glGetUniformLocation(m_shaderProgram, "uBozd"), Bozd.r, Bobj.g, Bozd.b, Bozd.a);
    glUniform1i(glGetUniformLocation(m_shaderProgram, "uTekID"), 0);

    //* vertex shader
    glm::mat4 matrika;
    matrika = glm::mat4(1);
    matrika = glm::translate(matrika, glm::vec3(poz.x, poz.y, poz.z));
    matrika = glm::rotate(matrika, glm::radians(rot), glm::vec3(0.0f, 0.0f, 1.0f));
    matrika = glm::scale(matrika, glm::vec3(vel.x, vel.y, vel.z));

    glUniformMatrix4fv(glGetUniformLocation(m_shaderProgram, "uTrans"), 1, GL_FALSE, &matrika[0][0]);
    glUniformMatrix4fv(glGetUniformLocation(m_shaderProgram, "uOrto"), 1, GL_FALSE, &m_orto[0][0]);
    glBindVertexArray(m_VAO);
    glUseProgram(m_shaderProgram);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}
uint32_t Risalnik::NaloziTeksturo(std::string potDoSlike)
{
    std::string pot = Risalnik::sredstvaPath + "/" + potDoSlike;
    uint32_t tekstura;
    glGenTextures(1, &tekstura);
    glBindTexture(GL_TEXTURE_2D, tekstura);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int dolzina, visina, kanali;
    stbi_set_flip_vertically_on_load(1);

    unsigned char *data = stbi_load(pot.c_str(), &dolzina, &visina, &kanali, 4);
    if (!data)
    {
        io::war(pot.c_str());
        io::err("NI SLIKE");
    }
    else
    {
        io::msg("SLIKA DELUJE");
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, dolzina, visina, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    }
    stbi_image_free(data);
    return tekstura;
}

void Risalnik::GumbCallBack(GLFWwindow *okno, int key, int scanCode, int akcija, int mods)
{
    if (key = GLFW_KEY_ESCAPE && akcija == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(m_okno, 1);
    }
}
