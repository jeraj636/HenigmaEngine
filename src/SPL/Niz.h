#pragma once
#include <iostream>
#include <cstring>
#include <string>
class Niz
{
public:
    Niz *operator=(std::string t_niz)
    {
        for (int i = 0; t_niz[i] != '\0'; i++)
        {
            m_niz[i] = t_niz[i];
            m_vel++;
            if (m_vel == m_dejVel)
                Realokiraj();
        }
        m_niz[m_vel] = '\0';
        return this;
    }
    Niz *operator=(const char *t_niz)
    {
        for (int i = 0; t_niz[i] != '\0'; i++)
        {
            m_niz[i] = t_niz[i];
            m_vel++;
            if (m_vel == m_dejVel)
                Realokiraj();
        }
        m_niz[m_vel] = '\0';
        return this;
    }
    Niz *operator+=(const char *t_niz)
    {
        for (int i = 0; t_niz[i] != '\0'; i++)
        {
            m_niz[m_vel] = t_niz[i];
            m_vel++;
            if (m_vel + i == m_dejVel)
                Realokiraj();
        }
        m_niz[m_vel] = '\0';
        return this;
    }
    Niz *operator+(const char *t_niz)
    {
        for (int i = 0; t_niz[i] != '\0'; i++)
        {
            m_niz[m_vel] = t_niz[i];
            m_vel++;
            if (m_vel + i == m_dejVel)
                Realokiraj();
        }
        m_niz[m_vel] = '\0';
        return this;
    }

    Niz *operator+=(std::string t_niz)
    {
        for (int i = 0; t_niz[i] != '\0'; i++)
        {
            m_niz[m_vel] = t_niz[i];
            m_vel++;
            if (m_vel + i == m_dejVel)
                Realokiraj();
        }
        m_niz[m_vel] = '\0';
        return this;
    }
    Niz *operator+(std::string t_niz)
    {
        for (int i = 0; t_niz[i] != '\0'; i++)
        {
            m_niz[m_vel] = t_niz[i];
            m_vel++;
            if (m_vel + i == m_dejVel)
                Realokiraj();
        }
        m_niz[m_vel] = '\0';
        return this;
    }
    char operator[](int i)
    {
        return *(m_niz + i);
    }

    int Velikost()
    {
        return m_vel;
    }

    char *CStr()
    {
        return m_niz;
    }

private:
    int m_vel = 0;
    char *m_niz = new char[16];
    int m_dejVel = 16;
    void Realokiraj()
    {
        char *novi = new char[m_dejVel * 2];
        memcpy(novi, m_niz, sizeof(char) * m_dejVel);
        delete (m_niz);
        m_niz = novi;
        m_dejVel *= 2;
    }
};