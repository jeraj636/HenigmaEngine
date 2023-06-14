

#include <stdint.h>
#include <string>

struct GLFWwindow;

class Risalnik
{
public:
    static void Init(const char *naslov);
    static void Zanka();
    std::string SredstvaPath;
    static bool AliSeMoramZapreti();

private:
    // static void VelikostOknaCallBack(GLFWwindow *okno, int dolzina, int visina);
    // static void GumbMiskeCallBack();
    // static void CharCallBack();
    static GLFWwindow *m_okno;
};
