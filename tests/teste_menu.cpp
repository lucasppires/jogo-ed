#include <iostream>
#include <fstream>
#include <string>
#include "funcoes_menu.hpp"
#include "cores.hpp"
#include "leitura_arquivos.hpp"
using std::cout;
using std::cin;
using std::scanf;
using std::endl;

// compilar: g++ tests/teste_menu.cpp src/funcoes_menu.cpp -I src -o tests/teste_menu.exe
// rodar: .\tests\teste_menu.exe 

int main(int argc, char *argv[])
{
    int ESTADO_MENU = MENU;

    while (ESTADO_MENU != SAIR)
        {

        while (ESTADO_MENU == MENU)
        {
            imprimir_menu(ESTADO_MENU);
        }

        if (ESTADO_MENU == NOVO_JOGO)
        {
            cout << "Novo jogo selecionado.";
            return 0;
        }
        else if (ESTADO_MENU == COMO_JOGAR)
        {
            como_jogar(ESTADO_MENU);
        }
        else if (ESTADO_MENU == HISTORICO)
        {
            cout << "Historico selecionado.";
            return 0;
        }
        else if (ESTADO_MENU == SAIR)
        {
            return 0;
        }

    }   


    return 0;
}