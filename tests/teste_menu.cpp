// Bibliotecas padrão
#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>

// TADs
#include "avl.hpp"
#include "lista.hpp"


// Bibliotecas do jogo
#include "cores.hpp"
#include "funcoes_menu.hpp"
#include "leitura_de_arquivos.hpp"
#include "timer.hpp"
#include "sortings.hpp"

using std::cout;
using std::cin;
using std::endl;
using std::scanf;

// compilar:g++ tests/teste_menu.cpp src/funcoes_menu.cpp src/leitura_de_arquivos.cpp src/lista.cpp src/avl.cpp src/timer.cpp src/sortings.cpp -I src -o tests/teste_menu.exe -Wall -std=c++17

// rodar: .\tests\teste_menu.exe src\pedidos.txt src\historico.txt

int main(int argc, char *argv[])
{
   if (confere_argc_e_argv(argc, argv) != 0) // verifica se os argumentos de linha de comando estão corretos
   {
      return 1;
   }

    ListaContEst lista_historico;  //crio e inicializo a lista contígua que vai armazenar o histórico de partidas
    inicializar(&lista_historico);

    double tempoHistorico = 0.0;
    int lidos = carregarPartidasListaContEst(argv[2], &lista_historico, &tempoHistorico);

    if (lidos < 0)
    {
        destruir(&lista_historico);
        return 1;
    }

    int ESTADO_MENU = MENU; //variavel que armazena o estado atual do menu, inicializado como MENU

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
            historicov3(ESTADO_MENU, &lista_historico);

        }
        else if (ESTADO_MENU == SAIR)
        {
            destruir(&lista_historico);
            return 0; //encerrar_programa();
        }

    }   


    return 0;
}