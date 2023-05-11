#pragma once
#include "Niz.h"
#include "Tabela.h"
#include "Hash.h"

template <class pt_kljuc, class pt_vr>
struct Seg
{
    Seg()
    {
    }
    pt_kljuc kljuc;
    pt_vr vr;
};
template <class pt_kljuc, class pt_vr>
class Zemljevid
{
public:
    Zemljevid(int t_dol)
        : m_gTab()
    {
        m_vel = 2 * t_dol;
        m_gTab.Porini(new Tabela<Seg>);
    }
    /*
    void Vstavi(pt_kljuc t_kljuc, pt_vr t_vr)
    {
        }
*/
private:
    struct Seg
    {
        Seg()
        {
        }
        pt_kljuc kljuc;
        pt_vr vr;
    };
    Tabela<Tabela<Seg *>> m_gTab;
    int m_vel;
};