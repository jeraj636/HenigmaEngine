#include "../../Include/Risalnik.h"
#include "../../Include/Log.h"
#include "../../Include/Font.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
void Risalnik::Narisi(uint32_t tekID, Barva Bobj, Barva Bozd, vec3 poz, float rot, vec3 vel)
{
    //* vertex shader
    glUniformMatrix4fv(glGetUniformLocation(m_shaderProgram, "uOrto"), 1, GL_FALSE, &m_orto[0][0]);

    glm::mat4 matrika;
    matrika = glm::mat4(1);
    matrika = glm::translate(matrika, glm::vec3(poz.x, poz.y, poz.z));
    matrika = glm::rotate(matrika, glm::radians(rot), glm::vec3(0.0f, 0.0f, 1.0f));
    matrika = glm::scale(matrika, glm::vec3(vel.x, vel.y, vel.z));

    glUniformMatrix4fv(glGetUniformLocation(m_shaderProgram, "uTrans"), 1, GL_FALSE, &matrika[0][0]);

    //* fragment shader

    glBindTexture(GL_TEXTURE_2D, tekID);

    glUniform1i(glGetUniformLocation(m_shaderProgram, "uTekID"), 0);

    glUniform4f(glGetUniformLocation(m_shaderProgram, "uBobj"), Bobj.r, Bobj.g, Bobj.b, Bobj.a);
    glUniform4f(glGetUniformLocation(m_shaderProgram, "uBozd"), Bozd.r, Bozd.g, Bozd.b, Bozd.a);

    glUseProgram(m_shaderProgram);
    glBindVertexArray(m_VAO);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Risalnik::NarisiZnak(Znak znak, Barva Bobj, Barva Bozd, vec3 poz, float rot, float vel)
{
    //* vertex shader
    glUniformMatrix4fv(glGetUniformLocation(m_shaderProgramB, "uOrto"), 1, GL_FALSE, &m_orto[0][0]);

    glm::mat4 matrika;
    matrika = glm::mat4(1);

    matrika = glm::translate(matrika, glm ::vec3(poz.x, poz.y, poz.z));
    matrika = glm::rotate(matrika, glm::radians(rot), glm::vec3(0.0f, 0.0f, 1.0f));
    matrika = glm::scale(matrika, glm::vec3((float)znak.velikost.x / znak.velikost.y * vel, vel, 0));

    glUniformMatrix4fv(glGetUniformLocation(m_shaderProgramB, "uTrans"), 1, GL_FALSE, &matrika[0][0]);

    //* fragment shader

    glBindTexture(GL_TEXTURE_2D, znak.tekID);

    glUniform1i(glGetUniformLocation(m_shaderProgramB, "uTekID"), 0);

    glUniform4f(glGetUniformLocation(m_shaderProgramB, "uBobj"), Bobj.r, Bobj.g, Bobj.b, Bobj.a);
    glUniform4f(glGetUniformLocation(m_shaderProgramB, "uBozd"), Bozd.r, Bozd.g, Bozd.b, Bozd.a);

    glBindVertexArray(m_VAOB);
    glUseProgram(m_shaderProgramB);

    glBindTexture(GL_TEXTURE_2D, znak.tekID);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, 0);
}