#pragma once
class Render;
class Scena
{
public:
    virtual void Zacetek(Render *Ren)
    {
        rend = Ren;
    };
    virtual void Konec() = 0;
    virtual void Zanka() = 0;
    Scena *Naslov()
    {
        return this;
    }

protected:
    Render *rend;
};