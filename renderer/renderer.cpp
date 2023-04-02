#include "renderer.h"
void Okno::zanka()
{
    glClearColor(barvaOdzadja.r, barvaOdzadja.g, barvaOdzadja.b, barvaOdzadja.a);
    glClear(GL_COLOR_BUFFER_BIT);
    for (int i = 0; i < tabScen.size(); i++)
    {
        if (tabScen[i]->aktivno)
            tabScen[i]->zanka();
    }
    glfwSwapBuffers(okno);
    glfwPollEvents();
}
Scena *Okno::dodajSceno()
{
    tabScen.push_back(new Scena(this));
    return tabScen.back();
}
Okno::Okno(int width, int height, const char *naslov)
    : barvaOdzadja(0xffffffff)
{
    if (!glfwInit())
        io::izpis("ni glfw-ja", io::type::error);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    okno = glfwCreateWindow(width, height, "HenigmaEngine", NULL, NULL);
    if (okno == NULL)
        io::izpis("ni okna", io::type::error);

    glfwMakeContextCurrent(okno);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        io::izpis("ni glada", io::type::error);

    glViewport(0, 0, width, width);

    glfwSetFramebufferSizeCallback(okno, posodobiVelikost);

    float tocke[20] = {
        1.0f,
        1.0f,
        0.0f,
        1.0f,
        1.0f,
        1.0f,
        -1.0f,
        0.0f,
        1.0f,
        0.0f,
        -1.0f,
        -1.0f,
        0.0f,
        0.0f,
        0.0f,
        -1.0f,
        1.0f,
        0.0f,
        0.0f,
        1.0f};
    uint indeksi[6] = {
        0, 1, 2,
        0, 2, 3};
    // uint VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    uint VBO;
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(tocke), tocke, GL_STATIC_DRAW);

    uint EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indeksi), indeksi, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    const char *vertexShaderSource = R"(
        #version 330 core
        layout (location=0) in vec3 APos;
        layout (location=1) in vec2 TPos;
        out vec2 Tpos;
        void main ()
        {
            gl_Position=vec4(APos,1.0);
            Tpos=TPos;
        }
    )";
    int uspeh;
    uint vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &uspeh);
    if (!uspeh)
        io::izpis("ni vetex shader-ja", io::type::error);

    const char *fragmentShaderSource = R"(
        #version 330 core
        in vec2 Tpos;

        uniform vec4 barva;
        //uniform sampler2d TID;
        out vec4 FragColor;
        void main ()
        {
            FragColor=vec4(barva);
        }
    )";
    uint fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &uspeh);
    if (!uspeh)
        io::izpis("ni fragment shader-ja", io::type::error);

    // uint shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &uspeh);
    if (!uspeh)
        io::izpis("ni shader programa", io::type::error);
    glDeleteShader(fragmentShader);
    glDeleteShader(vertexShader);
    glUseProgram(shaderProgram);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));
}
Okno::~Okno()
{
    for (int i = 0; i < tabScen.size(); i++)
        delete tabScen[i];
}