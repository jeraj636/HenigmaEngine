#pragma once
#include "Niz.h"
namespace spl
{
    int Hash(Niz t_niz)
    {
        int t = 0;
        for (int i = 0; i < t_niz.Velikost(); i++)
        {
            t += t_niz[i] * i * (113 * 11 + 1);
        }
        return t;
    }
    int Hash(std::string t_niz)
    {
        int t = 0;
        for (int i = 0; i < t_niz.size(); i++)
        {
            t += t_niz[i] * i * (113 * 11 + 1);
        }
        return t;
    }
    int Hash(const char *t_niz)
    {
        int t = 0;
        for (int i = 0; i < t_niz[i] != '\0'; i++)
        {
            t += t_niz[i] * i * (113 * 11 + 1);
        }
        return t;
    }
} // namespace SPL
