#include "renderer.h"
#include <iostream>
#include "../podEnote/scena/scena.h"
void Okno::zanka()
{
    if (glfwGetKey(okno, GLFW_KEY_ESCAPE))
        glfwSetWindowShouldClose(okno, 1);
    int dolzina, visina;
    glfwGetWindowSize(okno, &dolzina, &visina);
    pravopis = glm::ortho((float)-dolzina / 2, (float)dolzina / 2, (float)visina / 2, (float)-visina / 2);
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
    : barvaOdzadja(0xffffffff), pravopis(1)
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
        1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
        1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
        -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
        -1.0f, 1.0f, 0.0f, 0.0f, 1.0f};

    uint indeksi[6] = {
        0, 1, 2,
        0, 2, 3};
    // uint VAO;
    uint VBO;

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(tocke), tocke, GL_STATIC_DRAW);

    glGenVertexArrays(1, &BVAO);
    glBindVertexArray(BVAO);

    glGenBuffers(1, &BVBO);

    glBindBuffer(GL_ARRAY_BUFFER, BVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(tocke), tocke, GL_DYNAMIC_DRAW);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    uint EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indeksi), indeksi, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    glBindVertexArray(BVAO);
    glBindBuffer(GL_ARRAY_BUFFER, BVBO);
    uint BEBO;
    glGenBuffers(1, &BEBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, BEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indeksi), indeksi, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, BEBO);
    const char *vertexShaderSource = R"(
        #version 330 core
        layout (location=0) in vec3 APos;
        layout (location=1) in vec2 TPos;
        out vec2 Tpos;
        uniform mat4 poz;
        uniform mat4 pravopis;
        uniform mat4 SPoz;
        
        void main ()
        {
            //gl_Position =  pravopis * ((poz*SPoz )* (rot*SRot) * vel) * vec4(APos,1.0);
            gl_Position =  pravopis * poz * vec4(APos,1.0);
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
        uniform vec4 odzadje;
        uniform  sampler2D TID;
        out vec4 FragColor;
        void main ()
        {
            if(texture(TID,Tpos).a<=0.5)
            FragColor=vec4(odzadje);
            else
            FragColor=vec4(barva)*texture(TID,Tpos);

        }
    )";

    uint fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &uspeh);
    if (!uspeh)
    {
        char info[512];
        glGetShaderInfoLog(fragmentShader, 512, NULL, info);
        std::cout << info;
        io::izpis("ni fragment shader-ja", io::type::error);
    }

    // uint shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &uspeh);
    if (!uspeh)
        io::izpis("ni shader programa", io::type::error);
    glDeleteShader(fragmentShader);
    glUseProgram(shaderProgram);

    const char *besFragmentShaderSource = R"(
        #version 330 core
        in vec2 Tpos;

        uniform vec4 barva;
        uniform vec4 odzadje;
        uniform  sampler2D TID;
        out vec4 FragColor;
        void main ()
        {
            vec4 tek=texture(TID,Tpos);
            if(tek.r<0.6&&tek.g<0.6&&tek.b<0.6)
            FragColor=vec4(odzadje);
            else
            FragColor=vec4(barva)*texture(TID,Tpos);

        }
    )";
     uint BfragmentShader;
    BfragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(BfragmentShader, 1, &besFragmentShaderSource, NULL);
    glCompileShader(BfragmentShader);
    glGetShaderiv(BfragmentShader, GL_COMPILE_STATUS, &uspeh);
    if (!uspeh)
    {
        char info[512];
        glGetShaderInfoLog(BfragmentShader, 512, NULL, info);
        std::cout << info;
        io::izpis("ni fragment shader-ja", io::type::error);
    }

    BShaderProgram = glCreateProgram();
    glAttachShader(BShaderProgram, vertexShader);
    glAttachShader(BShaderProgram, BfragmentShader);
    glLinkProgram(BShaderProgram);
    glGetProgramiv(BShaderProgram, GL_LINK_STATUS, &uspeh);
    if (!uspeh)
        io::izpis("ni shader programa", io::type::error);
    glDeleteShader(fragmentShader);

    glDeleteShader(vertexShader);
    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));

    glUseProgram(BShaderProgram);
    glBindVertexArray(BVAO);
    glBindBuffer(GL_ARRAY_BUFFER, BVBO);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));

    pravopis = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f);
}
Okno::~Okno()
{
    for (int i = 0; i < tabScen.size(); i++)
        delete tabScen[i];
}