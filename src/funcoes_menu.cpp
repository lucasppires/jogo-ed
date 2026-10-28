#include <cstdio>
#include "funcoes_menu.hpp"

void imprime_linha(int n)
{
    for (int i = 0; i < n; i++)
        std::printf("#");
}

void pula_linha(int n)
{
    for (int i = 0; i < n; i++)
        std::printf("\n");
}