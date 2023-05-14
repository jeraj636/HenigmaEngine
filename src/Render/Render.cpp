#include "Render.h"
#include "../ostalo/ostalo.h"
Render::Render(std::string ime)
    : Odzadje(0xffffffff)
{
    // Init(ime);
}
void Render::Init(std::string ime)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_okno = glfwCreateWindow(800, 600, ime.c_str(), NULL, NULL);

    if (m_okno == NULL)
    {
        io::izpis("NI USTVARILO OKNA", io::type::error);
    }
    glfwMakeContextCurrent(m_okno);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        io::izpis("NI USTVARILO GLAD-a", io::type::error);
    }

    glfwSetFramebufferSizeCallback(m_okno, PosodobiVelOkna);

    NastaviShaderje();
    NastaviBuferje();

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);
}
bool Render::AliSeMoramZapreti()
{
    if (glfwWindowShouldClose(m_okno))
        return true;
    return false;
}
void Render::OkvirKon()
{
    glfwSwapBuffers(m_okno);
    glfwPollEvents();
}
void Render::OkvirZac()
{
    DobiVhod();
}
void Render::Zanka()
{
    glClearColor(Odzadje.r, Odzadje.g, Odzadje.b, Odzadje.a);
    glClear(GL_COLOR_BUFFER_BIT);
}
void Render::Narisi()
{
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Render::NastaviShaderje()
{
    int uspeh;
    const char *vertexShaderSource = R"(
            #version 330 core
            layout (location = 0) in vec3 Vpos;

            void main()
            {
                gl_Position = vec4(Vpos,1.0);
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
            void main()
            {
                FragColor=vec4(1.0,0.0,0.0,1.0);
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
    glGenVertexArrays(1, &m_SVAO);
    glBindVertexArray(m_SVAO);

    glGenBuffers(1, &m_SVBO);
    glBindBuffer(GL_ARRAY_BUFFER, m_SVBO);

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
    glGenBuffers(1, &m_SEBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_SEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indeksi), indeksi, GL_STATIC_DRAW);
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