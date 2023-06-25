#include "../../Include/Risalnik.h"
#include "../../Include/Log.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stdint.h>

void Risalnik::NaloziBufferje()
{
    float tocke[]{
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
        0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.0f, 1.0f, 1.0f,
        -0.5f, 0.5f, 0.0f, 0.0f, 1.0f};
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

    glUseProgram(m_shaderProgram);
    glBindVertexArray(m_VAO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void *)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void *)(sizeof(float) * 3));
    glEnableVertexAttribArray(1);
    glBindVertexArray(0);
}
void Risalnik::NaloziBufferjeB()
{
    float tocke[]{
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
        0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.0f, 1.0f, 1.0f,
        -0.5f, 0.5f, 0.0f, 0.0f, 1.0f};
    uint32_t indeksi[]{
        0, 1, 2,
        0, 2, 3};
    glGenVertexArrays(1, &m_VAOB);
    glBindVertexArray(m_VAOB);

    glGenBuffers(1, &m_VBOB);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBOB);
    glBufferData(GL_ARRAY_BUFFER, sizeof(tocke), tocke, GL_STATIC_DRAW);

    glGenBuffers(1, &m_EBOB);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBOB);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indeksi), indeksi, GL_STATIC_DRAW);

    glUseProgram(m_shaderProgramB);
    glBindVertexArray(m_VAOB);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void *)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void *)3);
    glEnableVertexAttribArray(1);
    glBindVertexArray(0);
}
