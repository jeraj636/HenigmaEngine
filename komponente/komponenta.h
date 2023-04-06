#pragma once

class Okno;
class Objekt;

class Komponenta
{
public:
    virtual void zanka() = 0;
    void nastavi(Okno *okn, Objekt *obj);

    Okno *okno;
    Objekt *objekt;
    bool aktivno = 1;

private:
};