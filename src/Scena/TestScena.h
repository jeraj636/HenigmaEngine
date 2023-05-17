#pragma once
#include "Scena.h"
#include <iostream>
class TestScena : public Scena
{
public:
    void Zacetek()
    {
        std::cout << "zacetek"<<std::endl;
    }
    void Konec()
    {
        std::cout << "konec"<<std::endl;
    }
    void Zanka()
    {
        std::cout << "zanka"<<std::endl;
    }
    Scena *Naslov()
    {
        return this;
    }
};