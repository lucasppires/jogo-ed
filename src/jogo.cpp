#include <iostream>
#include <string>
#include "jogo.hpp"
#include "fila.hpp"
#include "avl.hpp"
#include "pedido.hpp"
#include "timer.hpp"
#include "listacontest.hpp"
#include "funcoes_menu.hpp"
#include <random>
#include <stdexcept>
#include "teste_heap.hpp"
#include <fstream>
#include "avl.hpp"
#include "hash.hpp"
#include "heap.hpp"
#include "pilha.hpp"
#include "teste_pilha.hpp"


using std::cout;
using std::cin;
using std::scanf;
using std::endl;

using namespace std;

#define N_MAX_CLIENTES 10
#define N_CLIENTES 3

// essa funcao deve rodar no inicio de cada turno
void removeEstragadosHeap(int turnoAtual, FilaPrioridade *carnes, FilaPrioridade *ovos, FilaPrioridade *bacons)
{
    removeIngredienteEstragado(turnoAtual, carnes);
    removeIngredienteEstragado(turnoAtual, ovos);
    removeIngredienteEstragado(turnoAtual, bacons);
}




const Pedido *obterPedido(NodoAvl *raiz, TabelaEnc *cache, int codigo) 
{
    // Primeiro procura na hash.
    const Pedido *pedido = encBuscar(cache, codigo);

    if (pedido != nullptr)
        return pedido;

    // Se nao encontrou na hash, procura na AVL.
    NodoAvl *no = buscarPorCodigo(raiz, codigo);

    if (no == nullptr)
        return nullptr;

    // Guarda a referencia no cache para consultas futuras.
    encInserir(cache, codigo, &no->dado);

    return &no->dado;
}

// const pq o pedido sorteado nao deve ser modificado
const Pedido *sortearPedido(NodoAvl *raiz, TabelaEnc *cache)
{
    if (raiz == nullptr || cache == nullptr || cache->m <= 0)
        return nullptr;

    // Encontra o menor e o maior codigo presentes na AVL.
    const NodoAvl *menor = raiz;
    const NodoAvl *maior = raiz;

    while (menor->esq != nullptr)
        menor = menor->esq;

    while (maior->dir != nullptr)
        maior = maior->dir;

    const Pedido *pedido = nullptr;

    do
    {
        int codigo_sorteado = numero_aleatorio(menor->dado.cod, maior->dado.cod);

        // Consulta a hash e busca na AVL somente no miss.
        pedido = obterPedido(raiz, cache, codigo_sorteado);

        // Repete se o codigo sorteado nao existir.
    } while (pedido == nullptr);

    return pedido;
}



int numero_aleatorio(int minimo, int maximo)
{
    if (minimo > maximo)
        throw std::invalid_argument("Intervalo invalido");

    static std::mt19937 gerador(std::random_device{}());
    std::uniform_int_distribution<int> intervalo(minimo, maximo);

    return intervalo(gerador);
}

// teremos que trocar o nome pra argv[2]
void gravaJogoNoHistorico(){
    ofstream arq("historico_teste.txt", ios::app);
    if (!arq.is_open()) return;

    string nome;
    int score = 0;

    cout << "Nome:";
    getline(cin >> ws, nome);   // ws descarta o '\n' que sobrou de leituras anteriores

    cout << "Score:";
    cin >> score;

    arq << nome << '\n';                // linha 1: nome
    arq << score << '\n';               // linha 2: score

}

static void mostrarPerecivel(const char *nome,
                             const FilaPrioridade *estoque,
                             int turnoAtual)
{
    std::cout << nome << ": " << estoque->tamanho;

    int turnoVencimento;
    if (fpMinimo(estoque, &turnoVencimento))
    {
        int turnosRestantes = turnoVencimento - turnoAtual;
        std::cout << " | proximo vencimento em "
                  << turnosRestantes << " turno(s)";
    }

    std::cout << '\n';
}

static void mostrarEstoque(const FilaPrioridade *carnes,
                           const FilaPrioridade *ovos,
                           const FilaPrioridade *bacons,
                           const int quantidadesNaoPereciveis[],
                           int turnoAtual)
{
    std::cout << "\nESTOQUE - Turno " << turnoAtual << '\n';

    mostrarPerecivel("Carne", carnes, turnoAtual);
    mostrarPerecivel("Ovo frito", ovos, turnoAtual);
    mostrarPerecivel("Bacon", bacons, turnoAtual);

    std::cout << "Queijo suico: " << quantidadesNaoPereciveis[0] << '\n'
              << "Queijo cheddar: " << quantidadesNaoPereciveis[1] << '\n'
              << "Cebola: " << quantidadesNaoPereciveis[2] << '\n'
              << "Tomate: " << quantidadesNaoPereciveis[3] << '\n'
              << "Ilimitados: Pao de cima, Ketchup, "
              << "Mostarda, Picles e Alface\n";
}

void novoJogo(NodoAvl *raiz, TabelaEnc *cache, int &estado_menu, char *argv[], PilhaEnc *p, FilaPrioridade *carnes, FilaPrioridade *ovos, FilaPrioridade *bacons, int turnoAtual, int quantidadesPereciveisDisponiveis[], Jogador *player) {
    estado_menu = MENU;

    if (raiz == nullptr)
    {
        cout << "Nao existem pedidos para iniciar a partida.\n";
        return;
    }

    FilaEnc clientes;
    inicializa(&clientes);

    int numeroClientes = N_CLIENTES; // Número de clientes a serem criados

    // Valores provisorios: tres clientes com paciencias aleatorias.
    int pacienciaInicial[N_MAX_CLIENTES];

    for (int i = 0; i < numeroClientes; i++)
    {
        // sorteia um pedido e guarda na variavel
        const Pedido *pedidoAtual = sortearPedido(raiz, cache);

        if (pedidoAtual == nullptr) // Se não houver pedidos disponíveis
        {
            cout << "Nao foi possivel obter um pedido.\n";
            destruir(&clientes);
            return;
        }

        // vetor de numeros aleatorios, sorteamos uma paciencia para cada cliente, mas os valores podem se repetir
        pacienciaInicial[i] = numero_aleatorio(9, 15); //talvez criar algum algortimo para determinar a paciencia de forma mais adequada!!

        // criamos o cliente
        Cliente cliente_atual = criarCliente(i+1, pacienciaInicial[i], pedidoAtual);

        // enfileiramos o cliente na fila
        if (!enfileira(&clientes, cliente_atual))
        {
            cout << "Erro ao enfileirar os clientes.\n";
            destruir(&clientes);
            return;
        }
    }

    cout << "Partida iniciada com "
         << tamanho(&clientes) << " clientes.\n";

    turnoAtual = 0;

    player->score = 0;

    // LAÇO DO JOGO
    while (!estaVazia(&clientes))
     {     
        Cliente *atual = clienteDaFrente(&clientes);

        turnoAtual++;

        if (atual->paciencia_restante == 0) //gameover
        {
            esvaziarPilha(p);

            pula_linha(2);
            cout << cores::VERMELHO << "GAME OVER" << cores::RESET << " - A paciencia do cliente acabou!";
            break;  
        }

        pula_linha(2);

        cout << cores::LARANJA << "\nTurno " << turnoAtual << cores::RESET;

        if (atual->paciencia_restante == 1)
        {
            cout << " (ultimo!)\n";
        }
        else
        {
           pula_linha(1);
        }

        removeEstragadosHeap(turnoAtual, carnes, ovos, bacons);

        if (atual != nullptr) // Se houver clientes na fila
        {
            const Pedido *pedidoAtual = atual->pedido_cliente; //atribui o pedido do cliente ao pedido atual

            if (pedidoAtual == nullptr)
            {
                cout << "Cliente sem pedido associado.\n";
                destruir(&clientes);
                return;
            }

            cout << "\nCliente: " << atual->id << '\n';
            cout << "Paciencia restante: "<< atual->paciencia_restante << " turnos.\n"; 

            cout << "Pedido: " << pedidoAtual->cod << '\n';
            imprimir(&pedidoAtual->receita);

            // A montagem do hamburguer sera implementada aqui.
            int opcao;
            cout << "Informe a opcao desejada:\n"
                    << "1 - Adicionar ingrediente ao hamburguer\n"
                    << "2 - Remover ingrediente\n"
                    << "3 - Enviar pedido\n"
                    << "4 - Preparar ingrediente perecivel\n"
                    << "5 - Preparar ingrediente nao perecivel\n"
                    << "6 - Consultar estoque\n";
                    
            
            std::string entrada;

            while (true)  //equivale ao cin >> opcao, mas o cin da erro se for digitado um caractere no lugar de um int
            {
                if (!(cin >> entrada)) {
                    esvaziarPilha(p);
                    destruir(&clientes);
                    return;
                }

                if (entrada.size() == 1 && entrada[0] >= '1' && entrada[0] <= '6') {
                    opcao = entrada[0] - '0';
                    break;
                }

                if (entrada == "67") {
                    opcao = 67;
                    break;
                }

                cout << "Opcao invalida! Escolha de 1 a 6 ou 67: ";
            }

            switch (opcao) {
                case 1: {
                    char adicionado;
                    cout << "Informe o codigo do ingrediente que queres adicionar: " << endl;
                    cin >> adicionado;

                    const Ingrediente *ing = buscarIngrediente(adicionado);
                    if (ing == nullptr) {
                        cout << "Ingrediente invalido" << endl;
                    }
                    else if (ing->perecivel) {
                        // carne, ovo, bacon: so adiciona se tiver na heap (e remove de la)
                        usaIngredientePerecivel(adicionado, carnes, ovos, bacons, p);
                    }
                    else {
                        // resto: infinitos ou com contador de estoque
                        usaIngredienteNaoPerecivel(adicionado, quantidadesPereciveisDisponiveis, p);
                    }
                    break;
                }

                case 2:
                    remover_ingrediente(p);
                    break;

                case 3:
                case 67:  //passa de fase na hora
                    if (opcao == 67 || corrige_pedido(p, &pedidoAtual->receita)) {
                        if (opcao == 3) {
                            cout << "Pedido correto!" << endl;
                        }

                        Cliente atendido;
                        desenfileira(&clientes, &atendido);
                        esvaziarPilha(p);

                        player->score++;
                        turnoAtual = 0;

                        cout << "Cliente " << atendido.id
                             << " foi atendido e saiu da fila." << endl;
                        continue;
                    }

                    cout << "Montaste o hamburguer incorretamente! O cliente ficou putasso!" << endl;
                    atual->paciencia_restante--;
                    if (atual->paciencia_restante <= 0) {
                        Cliente removido;
                        desenfileira(&clientes, &removido);
                        esvaziarPilha(p);
                        cout << "Cliente " << removido.id
                             << " perdeu a paciencia e saiu da fila." << endl;
                        continue;
                    }
                    break;

                case 4:
                    prepararIngredientePerecivel(turnoAtual, carnes, ovos, bacons);
                break;
                    
                case 5:
                    prepararIngredienteNaoPerecivel(quantidadesPereciveisDisponiveis);
                break;

                case 6:
                    mostrarEstoque(carnes, ovos, bacons, quantidadesPereciveisDisponiveis, turnoAtual);
                    turnoAtual--;  //como consultar estoque nao gasta um turno, e em todo laço é acrescentado 1 ao turno, diminuimos 1 aqui para corrigir
                    atual->paciencia_restante++; //mesma coisa do turno
                break;
            
                default:
                    cout << "Opcao invalida" << endl;   //as vezes da um bug que faz o laço ficar em loop quando apertamos alguma opcao invalida
                break;

            }

            if (turnoAtual != 0)
            {
                imprimir_hamburguer(p);
            }

        }
            // O cliente continua na fila durante o atendimento.

        atual->paciencia_restante = atual->paciencia_restante - 1; 
        
    }

    pula_linha(1);
    cout << cores::VERDE_CLARO << "Sua pontuacao: " << player->score << cores::RESET;

    exibirEstatisticasHash(cache);
    destruir(&clientes);

}
