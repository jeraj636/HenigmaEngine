#pragma once
#include <cstring>
#include <iostream>
#include <vector>
template <class t>
class Tabela
{
public:
    Tabela()
    {
    }
    Tabela(int t_vel)
    {

        while (m_dejVel < t_vel)
        {
            Realokiraj();
        }
    }
    //* Na koncu doda element tipa t
    void Porini(t t_vrednost)
    {
        if (m_vel >= m_dejVel)
        {
            Realokiraj();
        }
        t neki;
        neki = t_vrednost;
        m_tab[m_vel] = t_vrednost;
        m_vel++;
    }
    //* Izbrisse element na koncu
    void Poci()
    {
        if (m_vel > 0)
            m_vel--;
    }
    //* na dolocenem indeksu vrine vrednost
    void Vstavi(t t_vrednost, int t_lok)
    {
        if (m_vel >= m_dejVel)
        {
            Realokiraj();
        }
        for (int i = m_vel; i < t_lok; i--)
        {
            m_tab[i] = m_tab[i - 1];
        }
        m_tab[t_lok] = t_vrednost;
    }
    //* vrne element na dolocenem indeksu
    t &Na(int t_lok)
    {
        if (t_lok < m_vel && t_lok >= 0)
            return *(m_tab + t_lok);
        return nullptr;
    }

    //* vrne element na dolocenem indeksu
    t &operator[](int t_lok)
    {

        return *(m_tab + t_lok);
    }
    //* Vrne zadnji element v tabeli
    t &Hrbet()
    {
        return *(m_tab + m_vel - 1);
    }
    //* Izbrise element na dolocenem indeksu
    void Izbris(int t_lok)
    {
        for (int i = t_lok; i < m_vel - 1; i++)
        {
            m_tab[i] = m_tab[i + 1];
        }
        m_vel--;
    }
    //* vrne velikost tabele
    int Vel()
    {
        return m_vel;
    }
    ~Tabela()
    {
        if (m_tab != nullptr)
        {
            delete[] m_tab;
            m_tab = nullptr;
        }
    }

private:
    t *m_tab = new t[4];
    int m_dejVel = 4;
    int m_vel = 0;

    void Realokiraj()
    {
        t *novi = new t[m_dejVel * 2];
        memcpy(novi, m_tab, sizeof(t) * m_dejVel);
        delete (m_tab);
        m_tab = novi;
        m_dejVel *= 2;
    }
};
