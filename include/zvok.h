#ifndef ZVOK_H
#define ZVOK_H
#include <miniaudio/mini_audio.h>
#include <string>
class Zvok;
class Muzika
{
public:
    static void init();

    friend class Zvok;

protected:
    static inline ma_result *m_rezultat;
    static inline ma_engine *m_engine;

private:
};
class Zvok
{
public:
    void nastavi(const std::string &pot);
    void predvajaj();
    void stop();
    bool ali_predvajam();
    void nastavi_loop(bool t);
    Zvok &operator=(const Zvok &z);
    void zacetek();
    void unici();

private:
    ma_sound *m_zvok;
    std::string m_pot;
};
#endif