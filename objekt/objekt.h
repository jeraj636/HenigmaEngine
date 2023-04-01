#pragma once
class Okno;
class Objekt
{
public:
    Okno *okno;
    Objekt(Okno *okn);
    void zanka();
    bool aktivno = 1;

private:
};