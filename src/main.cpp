// bibliotecas padrao
#include <iostream>
#include <string>

// TADs e funcoes do jogo
#include "avl.hpp"
#include "listacontest.hpp"
#include "hash.hpp"
#include "cores.hpp"
#include "funcoes_menu.hpp"
#include "leitura_de_arquivos.hpp"
#include "jogo.hpp"
#include "pilha.hpp"
#include "heap.hpp"
#include "medicoes.hpp"

using namespace std;

// compilar na raiz do projeto:
// g++ src/main.cpp src/funcoes_menu.cpp src/jogo.cpp src/fila.cpp src/leitura_de_arquivos.cpp src/listacontest.cpp src/listaenc.cpp src/ingredientes.cpp src/avl.cpp src/hash.cpp src/timer.cpp src/sortings.cpp src/heap.cpp src/pilha.cpp src/hamburguer.cpp src/preparo.cpp src/medicoes.cpp -I src -o dado_burger.exe -Wall -std=c++17
//
// executar no PowerShell:
// .\dado_burger.exe data\pedidos.txt data\historico.txt

int main(int argc, char *argv[])
{
    if (confere_argc_e_argv(argc, argv) != 0) // verifica se os argumentos de linha de comando estão corretos
    {
      return 1;
    }

    Metricas met; //guarda as metricas de desempenho, passada por referencia para as funcoes que medem algo

    NodoAvl *raiz = nullptr; //cria a raiz da arvore AVL que vai armazenar os pedidos
    double tempoPedidos = 0.0;

    int pedidosLidos = carregarPedidosAVL(argv[1], &raiz, &tempoPedidos, met); //carrega os pedidos do arquivo para a arvore AVL


    if (pedidosLidos < 0) 
    {
        raiz = avlDestruir(raiz); //se der erro na leitura do arquivo, destruo a arvore e retorno 1
        return 1;
    }

    met.nosInseridos = pedidosLidos;
    met.alturaAVL = avlAltura(raiz) + 1; // a especificacao pediu arvore vazia => altura 0 e arvore folha = altura = 1
    met.tempoCarga = tempoPedidos;

    // cout << pedidosLidos << " pedidos lidos em " << tempoPedidos << " segundos.\n";

    ListaContEst lista_historico;  //crio e inicializo a lista contígua que vai armazenar o histórico de partidas
    inicializar(&lista_historico);

    double tempoHistorico = 0.0;
    int historicoslidos = carregarPartidasListaContEst(argv[2], &lista_historico, &tempoHistorico);

    if (historicoslidos < 0) 
    {
        liberar_recursos(raiz, &lista_historico);
        return 1;
    }

    met.entradasHistorico = historicoslidos;

    iniciaLog("data/medicoes.log", met); //cria o arquivo de log e escreve as metricas que ja temos nele
    medirOrdenacaoHistorico(&lista_historico, met);

    TabelaEnc cache; 
    encInicializar(&cache, 11); //cria e inicializa a tabela hash que vai armazenar os pedidos sorteados, com m == 11

    Jogador player; //inicializamos o jogador

    int ESTADO_MENU = MENU; //variavel que armazena o estado atual do menu, inicializado como MENU

    int DIFICULDADE = 0; //determina se é facil , medio ou dificil

    while (ESTADO_MENU != SAIR) //enquanto o estado_menu nao for sair
        {

        if (ESTADO_MENU == MENU)
        {
            imprimir_menu(ESTADO_MENU);
        }

        if (ESTADO_MENU == NOVO_JOGO)
        {

            if (!selecionar_dificuldade(DIFICULDADE)) //se der erro na hora de selecionar a dificuldade
            {
                liberar_recursos(raiz, &lista_historico, &cache);
                return 0;
            }

            // cada partida comeca com hamburguer e estoques vazios
            PilhaEnc hamburguer;
            inicializa(&hamburguer);

            // Inicializam-se as min-heaps dos pereciveis
            FilaPrioridade carnes, ovos, bacons;
            fpInicializar(&carnes);
            fpInicializar(&ovos);
            fpInicializar(&bacons);

            // Inicializa-se o array dos não perecíveis
            int quantidades[4] = {0, 0, 0, 0}; // s, q, c, t

            //aqui chamamos a funcao que é o motor do jogo. 
            // é la que ocorrem a montagem de hamburgers, laços de turnos, etc
            novoJogo(raiz, &cache, ESTADO_MENU, argv, &hamburguer, &carnes, &ovos, &bacons, 0, quantidades, &player, met, &lista_historico, DIFICULDADE);
            
            ESTADO_MENU = MENU; //depois que acaba o jogo, volta automaticamente para o menu
        }
        else if (ESTADO_MENU == COMO_JOGAR)
        {
            como_jogar(ESTADO_MENU); //so mostra o texto explicando o jogo
        }
        else if (ESTADO_MENU == HISTORICO)
        {
            historicov3(ESTADO_MENU, &lista_historico, met); //exibe o historico, com diferentes formas de ordenamento

        }

    }   

    //se cair aqui, é pq o ESTADO_MENU é SAIR
    // evita o memory leak.
    liberar_recursos(raiz, &lista_historico, &cache);
    return 0; //encerrar_programa();
    
}
