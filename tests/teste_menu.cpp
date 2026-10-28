#include <iostream>
#include <fstream>
#include <string>
#include "funcoes_menu.hpp"

int main()
{
    imprime_linha(45);
    pula_linha(1);
    std::printf("\t\tDADO BURGER\n");
    pula_linha(1);
    std::printf("\t\t1. Novo jogo\n");
    std::printf("\t\t2. Como jogar\n");
    std::printf("\t\t3. Historico\n");
    pula_linha(1);
    imprime_linha(45);

    return 0;
}