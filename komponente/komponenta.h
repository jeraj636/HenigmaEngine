#pragma once
class Okno;
class Objekt;
class Komponenta
{
public:
    virtual void zanka()
    {
    }
    void nastavi(Okno *okn, Objekt *obj)
    {
        okno = okn;
        objekt = obj;
    }
    Okno *okno;
    Objekt *objekt;
    bool aktivno = 1;

private:
};