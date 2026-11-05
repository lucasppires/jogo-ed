#include <iostream>
#include "jogo.hpp"
#include "fila.hpp"
#include "avl.hpp"
#include "pedido.hpp"
#include "timer.hpp"
#include "listacontest.hpp"
#include "funcoes_menu.hpp"
#include <random>
#include <stdexcept>

using std::cout;
using std::cin;
using std::scanf;
using std::endl;

void novoJogo(NodoAvl *raiz, int &estado_menu, char *argv[]) 
{
    // Ao terminar esta funcao, o programa volta ao menu.
    estado_menu = MENU;

    if (raiz == nullptr)
    {
        cout << "Nao existem pedidos para iniciar a partida.\n";
        return;
    }

    FilaEnc clientes;
    inicializa(&clientes);

    // Valores provisorios: tres clientes com paciencias aleatorias.
    int pacienciaInicial = numero_aleatorio(9, 15);

    if (!criarClientes(&clientes, 3, pacienciaInicial)) {
        cout << "Erro ao criar os clientes.\n";
        destruir(&clientes);
        return;
    }

    cout << "Partida iniciada com " << tamanho(&clientes) << " clientes.\n";

    Cliente *atual = clienteDaFrente(&clientes);

    if (atual != nullptr) 
    {
        const Pedido *pedidoAtual = sortearPedido(raiz, argv);

        if (pedidoAtual == nullptr) 
        {
            cout << "Nao foi possivel obter um pedido.\n";
            destruir(&clientes);
            return;
        }

        cout << "\nCliente: " << atual->id << '\n';
        cout << "Paciencia: " << atual->paciencia_restante << " turnos.\n";

        cout << "Pedido: " << pedidoAtual->cod << '\n';
        imprimir(&pedidoAtual->receita);

        // A montagem do hamburguer sera implementada aqui.
        // O cliente continua na fila durante o atendimento.
    }

    destruir(&clientes);
}


int numero_aleatorio(int minimo, int maximo)
{
    if (minimo > maximo)
        throw std::invalid_argument("Intervalo invalido");

    static std::mt19937 gerador(std::random_device{}());
    std::uniform_int_distribution<int> intervalo(minimo, maximo);

    return intervalo(gerador);
}