#include "besedilo.h"
#include "../../renderer/renderer.h"
#include "../../objekt/objekt.h"
// #include "../../ostalo/ostalo.h"
#include "../transformacija/transformacija.h"
#include <iostream>
void Besedilo::zanka()
{
    glUseProgram(okno->shaderProgram);
    glBindVertexArray(okno->BVAO);
    glActiveTexture(GL_TEXTURE0);

    glBindTexture(GL_TEXTURE_2D, 1);

    glUniform1i(glGetUniformLocation(okno->shaderProgram, "TID"), 0);
    glUniform4f(glGetUniformLocation(okno->shaderProgram, "barva"), barvaOdzadja.r, barvaOdzadja.g, barvaOdzadja.b, barvaOdzadja.a);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    // io::izpis("tukaj", io::type::msg);

    glBindTexture(GL_TEXTURE_2D, _pisiava);
    glBindBuffer(GL_ARRAY_BUFFER, okno->BVBO);
    int i = 'a';

    float tocke[20] = {
        1.0f, 1.0f, 0.0f, lokacija[vsebina] + 1.0f / (float)95, 1.0f,
        1.0f, -1.0f, 0.0f, lokacija[vsebina] + 1.0f / (float)95, 0.0f,
        -1.0f, -1.0f, 0.0f, lokacija[vsebina], 0.0f,
        -1.0f, 1.0f, 0.0f, lokacija[vsebina], 1.0f};
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(tocke), tocke);
    glUniform1i(glGetUniformLocation(okno->shaderProgram, "TID"), 0);
    glUniform4f(glGetUniformLocation(okno->shaderProgram, "barva"), barvaObjekta.r, barvaObjekta.g, barvaObjekta.b, barvaObjekta.a);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
void Besedilo::nastavi(Okno *okn, Objekt *obj)
{
    io::izpis("objekt je nastavljen", io::type::msg);
    okno = okn;
    objekt = obj;
}
void Besedilo::naloziPisavo(const char *potDoPisave)
{
    _pisiava = naloziTeksturo(potDoPisave, 0);
    float x = 1.0 / 95;
    lokacija[32] = 0;
    for (int i = 33; i < 128; i++)
    {
        lokacija[i] = lokacija[i - 1] + x;
    }
}
Besedilo::Besedilo()
    : barvaObjekta(0xffffffff), barvaOdzadja(0x00000000)
{
}
