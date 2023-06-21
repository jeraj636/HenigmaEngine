#ifndef BARVA_H
#define BARVA_H
class Barva
{
public:
    float a, b, g, r;
    Barva(int hexCode)
    {
        SetUp(hexCode);
    }
    Barva()
    {
        a = 0;
        b = 0;
        g = 0;
        r = 0;
    }
    void Nastavi(int hexCode)
    {
        SetUp(hexCode);
    }
    void operator=(int hexcode)
    {
        SetUp(hexcode);
    }
    void operator=(Barva &bar)
    {
        r = bar.r;
        g = bar.g;
        b = bar.b;
        a = bar.a;
    }
    void operator=(Barva bar)
    {
        r = bar.r;
        g = bar.g;
        b = bar.b;
        a = bar.a;
    }

private:
    void SetUp(int hexCode)
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
#endif
