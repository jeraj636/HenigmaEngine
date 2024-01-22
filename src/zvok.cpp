#define MINIAUDIO_IMPLEMENTATION
#include "../include/zvok.h"
#include "../include/log.h"
#include <iostream>
void Muzika::init()
{
    m_rezultat = ma_engine_init(NULL, &m_engine);
    if (m_rezultat != MA_SUCCESS)
        log::err("NI MA_ENGINE");
}
void Zvok::nastavi(const std::string &pot)
{
    Muzika::m_rezultat = ma_sound_init_from_file(&Muzika::m_engine, pot.c_str(), 0, NULL, NULL, &m_zvok);

    if (Muzika::m_rezultat != MA_SUCCESS)
    {
        std::cout << pot << "\n";
        log::err("NI ZVOKA");
    }
}

void Zvok::predvajaj()
{
    ma_sound_start(&m_zvok);
}

void Zvok::stop()
{
    ma_sound_stop(&m_zvok);
}

bool Zvok::ali_predvajam()
{
    return ma_sound_is_playing(&m_zvok);
}

void Zvok::nastavi_loop(bool t)
{
    ma_sound_set_looping(&m_zvok, t);
}
