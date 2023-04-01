#include <fmt/core.h>
#include <fmt/color.h>
class Barva
{
public:
    float a, b, g, r;

    Barva(int hexCode)
    {
        a = hexCode & 0x000000ff;
        hexCode >>= 8;
        b = hexCode & 0x0000ff;
        hexCode >>= 8;
        g = hexCode & 0x00ff;
        hexCode >>= 8;
        r = hexCode & 0xff;
        a /= 0xff;
        r /= 0xff;
        g /= 0xff;
        b /= 0xff;
    }
};
namespace io
{
    enum class type
    {
        msg,
        warning,
        error
    };
    void izpis(const char *msg, const type &tip)
    {
        static int w = 0;
        static int s = 0;
        if (tip == type::error)
        {
            fmt::print(fg(fmt::color::red), "ERROR: {}\nKONEC PROGRAMA!\n", msg);
            exit(-1);
        }
        else if (tip == type::msg)
        {
            fmt::print(fg(fmt::color::green), "{}: MSG: ", s++);
            fmt::print("{}\n", msg);
        }
        else if (tip == type::warning)
        {
            fmt::print(fg(fmt::color::green), "{}: WARNING: ", w++);
            fmt::print("{}\n", msg);
        }
    }
}