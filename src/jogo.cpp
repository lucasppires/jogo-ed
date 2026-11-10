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

#define N_MAX_CLIENTES 10

void novoJogo(NodoAvl *raiz, TabelaEnc *cache, int &estado_menu, char *argv[])
{
    estado_menu = MENU;

    if (raiz == nullptr)
    {
        cout << "Nao existem pedidos para iniciar a partida.\n";
        return;
    }

    FilaEnc clientes;
    inicializa(&clientes);

    int numeroClientes = 3; // Número de clientes a serem criados

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
        pacienciaInicial[i] = numero_aleatorio(9, 15);

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

    Cliente *atual = clienteDaFrente(&clientes);

    if (atual != nullptr) // Se houver clientes na fila
    {
        const Pedido *pedidoAtual = atual->pedido_cliente;

        if (pedidoAtual == nullptr)
        {
            cout << "Cliente sem pedido associado.\n";
            destruir(&clientes);
            return;
        }

        cout << "\nCliente: " << atual->id << '\n';
        cout << "Paciencia: "
             << atual->paciencia_restante << " turnos.\n";

        cout << "Pedido: " << pedidoAtual->cod << '\n';
        imprimir(&pedidoAtual->receita);

        // A montagem do hamburguer sera implementada aqui.
        // O cliente continua na fila durante o atendimento.
    }


    exibirEstatisticasHash(cache);
    destruir(&clientes);

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