#include <iostream>
#include "SPL/Tabela.h"
#include <string>
#include "SPL/Niz.h"
#include "SPL/Zemljevid.h"
#include "SPL/Tabela.h"
int main()
{
    Tabela<Tabela<int>> tab(5);
    for (int i = 0; i < 5; i++)
    {
        // tab[i] = Tabela<int>(10);
        tab[i] = Tabela<int>();
    }
}