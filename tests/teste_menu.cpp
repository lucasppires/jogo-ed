#include <iostream>
#include <fstream>
#include <string>
#include "funcoes_menu.hpp"
#include "cores.hpp"
using std::cout;
using std::cin;
using std::scanf;
using std::endl;

// compilar: g++ tests/teste_menu.cpp src/funcoes_menu.cpp -I src -o tests/teste_menu.exe
// rodar: .\tests\teste_menu.exe 

int main()
{
    int ESTADO_MENU = MENU;

    while (ESTADO_MENU != SAIR)
        {

        while (ESTADO_MENU == MENU)
        {
            imprime_linha(44);
            pula_linha(1);
            cout << cores::AZUL <<"\t\tDADO BURGER\n";
            pula_linha(1);
            cout << cores::AMARELO <<"\t\t1. Novo jogo\n";
            cout << cores::VERMELHO <<"\t\t2. Como jogar\n";
            cout << cores::VERDE <<"\t\t3. Historico\n";
            cout << cores::MAGENTA <<"\t\t4. Sair\n" << cores::RESET;
        
            pula_linha(1);
            imprime_linha(44);
            pula_linha(2);

            cout << "Digite a opcao desejada: ";

            cin >> ESTADO_MENU;
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