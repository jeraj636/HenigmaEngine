#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "ostalo/ostalo.h"
#include <iostream>
void posodobiVelikost(GLFWwindow *okko, int width, int height);

int main()
{
    if (!glfwInit())
        io::izpis("ni glfw-ja", io::type::error);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *okno = glfwCreateWindow(800, 600, "HenigmaEngine", NULL, NULL);
    if (okno == NULL)
        io::izpis("ni okna", io::type::error);

    glfwMakeContextCurrent(okno);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        io::izpis("ni glada", io::type::error);

    glViewport(0, 0, 800, 600);

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
    uint VAO;
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

    uint shaderProgram;
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
    Barva b(0xffff00ff);
    while (!glfwWindowShouldClose(okno))
    {
        glClearColor(0.2, 0.3, 0.5, 1);
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glUniform4f(glGetUniformLocation(shaderProgram, "barva"), b.r, b.g, b.b, b.a);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glfwSwapBuffers(okno);
        glfwPollEvents();
    };
    glfwTerminate();
    return 0;
}
void posodobiVelikost(GLFWwindow *okko, int width, int height)
{
    glViewport(0, 0, width, height);
}