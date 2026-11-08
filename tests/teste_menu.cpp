// Bibliotecas padrão
#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>

// TADs
#include "avl.hpp"
#include "listacontest.hpp"
#include "hash.hpp"


// Bibliotecas do jogo
#include "cores.hpp"
#include "funcoes_menu.hpp"
#include "leitura_de_arquivos.hpp"
#include "timer.hpp"
#include "sortings.hpp"
#include "jogo.hpp"


using std::cout;
using std::cin;
using std::endl;
using std::scanf;

// compilar: g++ tests/teste_menu.cpp src/funcoes_menu.cpp src/jogo.cpp src/fila.cpp src/leitura_de_arquivos.cpp src/listacontest.cpp src/listaenc.cpp src/ingredientes.cpp src/avl.cpp src/hash.cpp src/timer.cpp src/sortings.cpp -I src -o tests/teste_menu.exe -Wall -std=c++17

// rodar: .\tests\teste_menu.exe src\pedidos.txt src\historico.txt

int main(int argc, char *argv[])
{
   if (confere_argc_e_argv(argc, argv) != 0) // verifica se os argumentos de linha de comando estão corretos
   {
      return 1;
   }

    NodoAvl *raiz = nullptr; //cria a raiz da arvore AVL que vai armazenar os pedidos
    double tempoPedidos = 0.0;

    int pedidosLidos = carregarPedidosAVL(argv[1], &raiz, &tempoPedidos); //carrega os pedidos do arquivo para a arvore AVL

    if (pedidosLidos < 0) 
    {
        raiz = avlDestruir(raiz); //se der erro na leitura do arquivo, destruo a arvore e retorno 1
        return 1;
    }

    cout << pedidosLidos << " pedidos lidos em " << tempoPedidos << " segundos.\n";

    ListaContEst lista_historico;  //crio e inicializo a lista contígua que vai armazenar o histórico de partidas
    inicializar(&lista_historico);

    double tempoHistorico = 0.0;
    int historicoslidos = carregarPartidasListaContEst(argv[2], &lista_historico, &tempoHistorico);

    if (historicoslidos < 0)
    {
        liberar_recursos(raiz, &lista_historico);
        return 1;
    }

    TabelaEnc cache; 
    encInicializar(&cache, 101); //cria e inicializa a tabela hash que vai armazenar os pedidos mais recentes

    int ESTADO_MENU = MENU; //variavel que armazena o estado atual do menu, inicializado como MENU

    while (ESTADO_MENU != SAIR)
        {

        if (ESTADO_MENU == MENU)
        {
            imprimir_menu(ESTADO_MENU);
        }

        if (ESTADO_MENU == NOVO_JOGO)
        {
            novoJogo(raiz, &cache, ESTADO_MENU, argv);
            ESTADO_MENU = MENU;
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

            liberar_recursos(raiz, &lista_historico, &cache);
            return 0; //encerrar_programa();
        }

    }   


    return 0;
}
