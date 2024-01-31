#include "../include/ploscice.h"
#include "../include/risalnik.h"

void Ploscice::nastavi(char *zemljevid, int x, int y, char prepoznavni_znak, uint32_t tek_id, uint32_t barva_obj)
{

    if (m_tocke)
        delete[] m_tocke;
    if (m_indeksi)
        delete[] m_indeksi;

    velikost = mat::vec2(Risalnik::get_velikost_okna().x / x, Risalnik::get_velikost_okna().y / y);
    barva_objekta = barva_obj;
    tekstura_id = tek_id;

    m_n = 0;
    for (int i = 1; i < y + 1; i++)
    {
        for (int j = 1; j < x + 1; j++)
        {
            if (prepoznavni_znak == zemljevid[i * (x + 2) + j])
                m_n++;
        }
    }

    mat::vec2 *tab_poz = new mat::vec2[m_n];

    int t = 0;
    for (int i = 1; i < y + 1; i++)
    {
        for (int j = 1; j < x + 1; j++)
        {
            if (zemljevid[i * (x + 2) + j] == prepoznavni_znak)
            {
                tab_poz[t].x = j * velikost.x - velikost.x / 2;
                tab_poz[t].y = i * velikost.y - velikost.y / 2;
                t++;
            }
        }
    }

    m_tocke = new float[16 * m_n];
    m_indeksi = new uint32_t[6 * m_n];

    mat::vec2 t_vel = velikost;
    t_vel.x /= 2;
    t_vel.y /= 2;

    for (int i = 0; i < m_n; i++)
    {
        m_tocke[i * 16 + 0] = tab_poz[i].x - t_vel.x;
        m_tocke[i * 16 + 1] = tab_poz[i].y - t_vel.y;
        m_tocke[i * 16 + 2] = 0.0f;
        m_tocke[i * 16 + 3] = 0.0f;

        m_tocke[i * 16 + 4] = tab_poz[i].x + t_vel.x;
        m_tocke[i * 16 + 5] = tab_poz[i].y - t_vel.y;
        m_tocke[i * 16 + 6] = 1.0f;
        m_tocke[i * 16 + 7] = 0.0f;

        m_tocke[i * 16 + 8] = tab_poz[i].x + t_vel.x;
        m_tocke[i * 16 + 9] = tab_poz[i].y + t_vel.y;
        m_tocke[i * 16 + 10] = 1.0f;
        m_tocke[i * 16 + 11] = 1.0f;

        m_tocke[i * 16 + 12] = tab_poz[i].x - t_vel.x;
        m_tocke[i * 16 + 13] = tab_poz[i].y + t_vel.y;
        m_tocke[i * 16 + 14] = 0.0f;
        m_tocke[i * 16 + 15] = 1.0f;

        m_indeksi[i * 6 + 0] = 0 + i * 4;
        m_indeksi[i * 6 + 1] = 1 + i * 4;
        m_indeksi[i * 6 + 2] = 2 + i * 4;
        m_indeksi[i * 6 + 3] = 0 + i * 4;
        m_indeksi[i * 6 + 4] = 2 + i * 4;
        m_indeksi[i * 6 + 5] = 3 + i * 4;
    }
    delete[] tab_poz;
}

void Ploscice::narisi_me()
{
    Risalnik::narisi_ploscice(tekstura_id, barva_objekta, m_tocke, m_indeksi, m_n);
}

void Ploscice::unici()
{
    delete[] m_tocke;
    delete[] m_indeksi;
    m_tocke = nullptr;
    m_indeksi = nullptr;
}
Ploscice::Ploscice()
{
    m_tocke = nullptr;
    m_indeksi = nullptr;
}