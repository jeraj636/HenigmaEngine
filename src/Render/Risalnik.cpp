#include "Render.h"
void Render::Narisi(uint32_t &tekstura, spl::vec3 poz, float rot, spl::vec3 vel, Barva obj, Barva ozd)
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, tekstura);

    glUniform1i(glGetUniformLocation(m_shaderProgram, "tekID"), 0);

    glUniform4f(glGetUniformLocation(m_shaderProgram, "obj"), obj.r, obj.g, obj.b, obj.a);
    glUniform4f(glGetUniformLocation(m_shaderProgram, "ozd"), ozd.r, ozd.g, ozd.b, ozd.a);

    glUniformMatrix4fv(glGetUniformLocation(m_shaderProgram, "proj"), 1, GL_FALSE, &m_proj[0][0]);

    glm::mat4 matrika = glm::mat4(1);

    matrika = glm::translate(matrika, glm::vec3(poz.x, poz.y, 0));

    matrika = glm::scale(matrika, glm::vec3(vel.x, vel.y, 0));

    matrika = glm::rotate(matrika, glm::radians(rot), glm::vec3(0, 0, 1));
    glUniformMatrix4fv(glGetUniformLocation(m_shaderProgram, "matrika"), 1, GL_FALSE, &matrika[0][0]);

    glBindVertexArray(m_SVAO);
    glUseProgram(m_shaderProgram);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
void Render::NarisiZnak(Znak &znak, spl::vec3 poz, float rot, Barva BObj, Barva BOzd)
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, znak.TeksturaID);

    glm::mat4 matrika = glm::mat4(1);
    matrika = glm::translate(matrika, glm::vec3(poz.x, poz.y, poz.z));
    matrika = glm::scale(matrika, glm::vec3(znak.velikost.x, znak.velikost.y, 0.0f));
    matrika = glm::rotate(matrika, glm::radians(rot), glm::vec3(0, 0, 1));

    glUniformMatrix4fv(glGetUniformLocation(m_shaderProgramBes, "matrika"), 1, GL_FALSE, &matrika[0][0]);
    glUniformMatrix4fv(glGetUniformLocation(m_shaderProgramBes, "proj"), 1, GL_FALSE, &m_proj[0][0]);

    glUniform1i(glGetUniformLocation(m_shaderProgramBes, "TekID"), 0);

    glUniform4f(glGetUniformLocation(m_shaderProgramBes, "textColor"), BObj.r, BObj.g, BObj.b, BObj.a);

    glUniform4f(glGetUniformLocation(m_shaderProgramBes, "ozdColor"), BOzd.r, BOzd.g, BOzd.b, BOzd.a);

    glBindVertexArray(m_SVAO);
    glUseProgram(m_shaderProgramBes);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
void Render::NarisiNiz(const std::string &vsebina, Font &font, spl::vec3 poz, float rot, spl::vec3 vel, Barva BObj, Barva BOzd)
{
    // spl::vec3 dejPoz = poz;
    for (int i = 0; i < vsebina.size(); i++)
    {
        // std::cout << vsebina[i];
        // poz.y += font.znaki[vsebina[i]].ofset.y;
        NarisiZnak(font.znaki[vsebina.at(i)], poz - spl::vec3(font.znaki[vsebina[i]].ofset.x, font.znaki[vsebina[i]].ofset.y, 0), rot, BObj, BOzd);
        poz.x += vel.x * 2 + font.znaki[vsebina[i]].odmik / 100;
    }
}