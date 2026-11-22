#include <iostream>

using namespace std;
#include <fstream>
#include <string>
#include "funcoes_menu.hpp"
#include "cores.hpp"
#include "leitura_de_arquivos.hpp"
#include "listacontest.hpp"
#include "sortings.hpp"
#include "avl.hpp"
#include "fila.hpp"
#include "timer.hpp"
#include <random>
#include <stdexcept>
#include "medicoes.hpp"
#include <vector>
#include <limits>

void imprime_linha(int n)
{
    for (int i = 0; i < n; i++)
        printf("#");
}

void pula_linha(int n)
{
    for (int i = 0; i < n; i++)
        printf("\n");
}

void imprimir_menu(int& estado_menu)
{
    // espacos fixos deixam o menu alinhado em terminais diferentes

    cout << '\n'
         << cores::AZUL_CLARO
         << "  ----------------------------------------------------------\n"
         << cores::LARANJA
         << "                        .--------.\n"
         << "                     .-'  . . .   '-.\n"
         << "                    /________________\\\n"
         << cores::VERDE_CLARO << "                    /\\/\\/\\/\\/\\/\\/\\/\\/\\\n"
         << cores::MARROM << "                    [################]\n"
         << cores::LARANJA << "                    \\________________/\n\n"
         << cores::AMARELO_CLARO << "                        DADO BURGER\n"
         << cores::AZUL_CLARO
         << "  ----------------------------------------------------------\n\n"
         << cores::VERDE_CLARO << "       [1]  " << cores::BRANCO_CLARO << "Novo jogo\n\n"
         << cores::CIANO_CLARO << "       [2]  " << cores::BRANCO_CLARO << "Como jogar\n\n"
         << cores::AMARELO_CLARO << "       [3]  " << cores::BRANCO_CLARO << "Historico\n\n"
         << cores::VERMELHO_CLARO << "       [4]  " << cores::BRANCO_CLARO << "Sair\n\n"
         << cores::AZUL_CLARO
         << "  ----------------------------------------------------------\n"
         << cores::RESET;

    string opcao;

    while (true)
    {
        cout << cores::CIANO_CLARO << "  Escolha uma opcao [1-4]: " << cores::RESET;

        if (!(cin >> opcao)) {
            estado_menu = SAIR; // sai se a entrada for encerrada
            break;
        }

        if (opcao.size() == 1 && opcao[0] >= '1' && opcao[0] <= '4') {
            estado_menu = opcao[0] - '0';
            break;
        }

        cout << cores::VERMELHO_CLARO
             << "  Opcao invalida! Escolha de 1 a 4.\n"
             << cores::RESET;
    }
}

//destroi a avl e a lista contígua de histórico
void liberar_recursos(NodoAvl *&raiz, ListaContEst *lista_historico, TabelaEnc *cache)
{
    
    // libera o cache antes dos pedidos aos quais ele aponta
    if (cache != nullptr) {
        encDestruir(cache);
    }

    raiz = avlDestruir(raiz);
    destruir(lista_historico);
}

// devolve false se a entrada for encerrada antes de escolher uma dificuldade
bool selecionar_dificuldade(int &dificuldade)
{
    pula_linha(2);
    cout << cores::VERDE_CLARO << "1 - Facil\n"
         << cores::AMARELO_CLARO << "2 - Normal\n"
         << cores::VERMELHO_CLARO << "3 - Dificil\n\n"
         << cores::RESET;

    string opcaoDificuldade;
    while (true) {
        cout << "Selecione um nivel de dificuldade [1-3]: ";

        if (!(cin >> opcaoDificuldade)) {
            return false;
        }

        // aceita somente um digito entre 1 e 3
        if (opcaoDificuldade.size() == 1 && opcaoDificuldade[0] >= '1' && opcaoDificuldade[0] <= '3') 
        {
            // os valores de FACIL, NORMAL e DIFICIL sao 2, 3 e 4
            dificuldade = opcaoDificuldade[0] - '0' + 1;
            pula_linha(2);
            return true;
        }

        cout << cores::VERMELHO_CLARO << "Opcao invalida! Escolha 1, 2 ou 3." << cores::RESET;

        pula_linha(1);
    }
}

void como_jogar(int& estado_menu)
{
    cout << R"(
    COMO JOGAR - DADO BURGER

    Atenda os 3 clientes da partida, na ordem de chegada.
    Cada cliente tem uma receita e sua propria paciencia.
    Somente o cliente da frente perde paciencia enquanto e atendido.

    DIFICULDADE E PONTUACAO
    A paciencia inicial depende dos turnos para preparar e montar a
    receita, incluindo 1 turno reservado para enviar o pedido.

    Facil    - 4 turnos de margem e multiplicador de pontos x1.
    Normal   - 2 turnos de margem e multiplicador de pontos x1,5.
    Dificil  - sem margem adicional e multiplicador de pontos x2.

    A cada atendimento concluido, voce recebe
    10 x paciencia restante x multiplicador da dificuldade.
    A pontuacao final e a soma dos pontos dos clientes atendidos.

    MONTANDO O PEDIDO
    Confira a receita e adicione os ingredientes na ordem indicada,
    de baixo para cima. O pao de baixo ja esta no prato.
    Coloque o pao de cima (z) por ultimo e escolha Enviar pedido.
    O hamburguer precisa corresponder exatamente a receita.

    Voce so pode remover o ingrediente do topo. Ele e descartado
    e nao volta ao estoque. O pao de baixo permanece no prato.
    Depois do pao de cima, remova-o antes de adicionar outra camada.

    INGREDIENTES
    Sem preparo e com quantidade ilimitada
    z - Pao de cima    k - Ketchup    m - Mostarda
    p - Picles        a - Alface

    Precisam de preparo e permanecem no estoque sem vencer
    s - Queijo suico   q - Queijo cheddar
    c - Cebola        t - Tomate

    Precisam de preparo e vencem no estoque
    n - Carne - Validade: 4 turnos
    o - Ovo frito - Validade: 2 turnos
    b - Bacon - Validade: 3 turnos
    

    ACOES NA PARTIDA
    1 - Adicionar um ingrediente ao hamburguer.
    2 - Remover o ingrediente do topo.
    3 - Enviar o pedido para conferir a montagem e atender o cliente.
    4 - Preparar uma unidade de carne, ovo ou bacon.
    5 - Preparar uma unidade de queijo, cebola ou tomate.
    6 - Consultar o estoque.
    7 - Encerrar a partida e guardar a pontuacao obtida.

    Preparar, adicionar e remover consomem 1 turno por tentativa.
    Enviar um pedido incorreto tambem consome 1 turno.
    Ao enviar corretamente, o proximo cliente passa a ser atendido.
    Consultar o estoque e sair nao consomem turno.
    A receita e o hamburguer atual aparecem na tela de acoes.

    ESTOQUE E VALIDADE
    Prepare as unidades necessarias antes de adiciona-las.
    Para usar um ingrediente preparado, deve haver uma unidade
    disponivel no estoque. Ao usa-la, a quantidade diminui em 1.

    No inicio de cada turno, as unidades pereciveis vencidas sao
    descartadas. Uma unidade preparada no turno 1 vence no inicio
    do turno 4. Ao usar um perecivel, sai primeiro o que vence antes.

    Na consulta ao estoque, voce ve as quantidades e quantos turnos
    faltam para o proximo vencimento. Para voltar, digite uma tecla
    e pressione Enter.

    FIM DA PARTIDA
    Atenda todos os clientes para vencer.
    Se a paciencia do cliente da frente acabar com o pedido pendente,
    a partida termina em GAME OVER. Voce tambem pode sair pela opcao 7.

    No encerramento, informe um nome com ate 20 caracteres para salvar
    sua pontuacao. O Relatorio de Desempenho e exibido em seguida.
    No menu Historico, escolha a ordem por pontuacao ou por nome.

    Selecione uma opcao

    1. Jogar
    2. Voltar ao menu
    )";

    int opcao;
    cin >> opcao;

    if (opcao == 1)
    {
        estado_menu = NOVO_JOGO;
    }
    else if (opcao == 2)
    {
        estado_menu = MENU;
    }
}

void historico(int& estado_menu, ListaContEst *lista_historico)
{
    imprimir_ListaContEst(lista_historico);

    cout << "\nSelecione uma opcao:\n";
    cout << "1. Jogar\n";
    cout << "2. Voltar ao menu\n";

    int opcao;
    cin >> opcao;

    if (opcao == 1)
    {
        estado_menu = NOVO_JOGO;
    }
    else if (opcao == 2)
    {
        estado_menu = MENU;
    }
}

/*
void historicov2(int& estado_menu, ListaContEst *lista_historico)
{
    //imprimir_ListaContEst(lista_historico);
    jogador *vetor = new Jogador[lista_historico->tamanho];

    // ordenamos a copia para preservar a ordem original das partidas na lista
    int tamanhoVetor = lista_para_vetor(lista_historico, vetor);

    double tempo = ordena_vetor_pelo_score_bubble_sort(vetor, tamanhoVetor);

    imprime_dez_primeiros(vetor);
    printf("\nTempo para ordenar (Bubble sort): %fs\n", tempo);

    delete[] vetor;

    cout << "\nSelecione uma opcao:\n";
    cout << "1. Jogar\n";
    cout << "2. Voltar ao menu\n";

    int opcao;
    cin >> opcao;

    if (opcao == 1)
    {
        estado_menu = NOVO_JOGO;
    }
    else if (opcao == 2)
    {
        estado_menu = MENU;
    }
}
*/

//usa merge sort
void historicov3(int& estado_menu, ListaContEst *lista_historico, Metricas &met)
{

    if (lista_historico->tamanho == 0)
    {
        cout << "Historico vazio.\n";
        estado_menu = MENU;
        return;
    }

    int res;

    Jogador *vetor = new Jogador[lista_historico->tamanho]; //aloca com new o vetor do tamanho da lista de jogadores

    int tamanhoVetor = lista_para_vetor(lista_historico, vetor);

    cout << "Como queres visualizar o historico? Por score [1] ou por nome [2]:" << endl;
    cin >> res;

    bool ehPorScore;

    switch (res){
        case 1:  // por score
        {
            double tempo = mergeSortAdaptado(vetor, tamanhoVetor);

            met.tamanhoOrdenacao = tamanhoVetor;   // atualiza o que sai no Relatorio de Desempenho
            met.tempoOrdenacao = tempo;

            registraOrdenacao("data/medicoes.log", tamanhoVetor, "Merge Sort (scores)", tempo);

            ehPorScore = true;
            
            if (lista_historico->tamanho < 10) 
            {
                imprime_de_1_a_9(vetor, tamanhoVetor, ehPorScore); //se tiver entre 1 e 9 jogadores, imprimimos todos eles
            }
            else
            {
            imprime_dez_primeiros(vetor, ehPorScore); //se tiver 10 ou mais, imprimimos apenas os top 10
            }

            printf("\nOrdenou %d jogadores.", tamanhoVetor);
            printf("\nTempo para ordenar (Merge Sort): %fs\n", tempo);

        }
        break;

        case 2:     // por ordem alfabetica
        {
            double tempoOrdString = quickSortAdaptado(vetor, tamanhoVetor);

            met.tamanhoOrdenacao = tamanhoVetor;
            met.tempoOrdenacao = tempoOrdString;
            registraOrdenacao("data/medicoes.log", tamanhoVetor, "Quick Sort (nomes)", tempoOrdString);

            ehPorScore = false;

            if (lista_historico->tamanho < 10) 
            {
                imprime_de_1_a_9(vetor, tamanhoVetor, ehPorScore); //se tiver entre 1 e 9 jogadores, imprimimos todos eles
            }
            else
            {
            imprime_dez_primeiros(vetor, ehPorScore); //se tiver 10 ou mais, imprimimos apenas os top 10
            }

            printf("\nOrdenou %d jogadores.", tamanhoVetor);
            printf("\nTempo para ordenar (Quick Sort): %fs\n", tempoOrdString);

        }
        break;

        default:
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        break;
    }

    delete[] vetor;

    cout << "\nSelecione uma opcao:\n";
    cout << "1. Jogar\n";
    cout << "2. Voltar ao menu\n";

    int opcao;
    cin >> opcao;

    if (opcao == 1)
    {
        estado_menu = NOVO_JOGO;
    }
    else if (opcao == 2)
    {
        estado_menu = MENU;
    }
}

// funcao pra por no medicoes.log infos sobre a ordenacao do historico
void medirOrdenacaoHistorico(ListaContEst *lista_historico, Metricas &met)
{
    if (lista_historico->tamanho == 0) return;

    Jogador *vetor = new Jogador[lista_historico->tamanho];
    int tamanhoVetor = lista_para_vetor(lista_historico, vetor);   // cópia, fora do tempo

    double tempo = mergeSortAdaptado(vetor, tamanhoVetor);         // só a ordenação

    met.tamanhoOrdenacao = tamanhoVetor;
    met.tempoOrdenacao = tempo;

    delete[] vetor;
}
