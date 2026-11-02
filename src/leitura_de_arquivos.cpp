#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <filesystem>
#include <system_error>

#include "avl.hpp"
#include "lista.hpp"
#include "timer.hpp"

using std::cerr;
using std::ifstream;
using std::string;
using std::cout;
using std::cin;

int carregarPedidosAVL(
    const char *arquivo,
    NodoAvl **raiz,
    double *tempo)
{

    std::ifstream arq(arquivo);

    if (!arq)
    {
        std::cerr << "Nao foi possivel abrir o arquivo.\n";
        return -1;
    }

    int codigo;
    std::string receita;
    int qtePedidosLidos = 0;

    Timer t;
    timer_iniciar(&t);

    while (arq >> codigo >> receita)
    {
        Pedido pedido;
        pedido.cod = codigo;
        pedido.receita = receita;

        *raiz = avlInserir(*raiz, pedido);

        qtePedidosLidos++;
    }

    *tempo = timer_parar(&t);

    return qtePedidosLidos;
}

int confere_argc_e_argv(int argc, char *argv[])
{
    if (argc < 3)
        {
            cerr << "Uso: " << argv[0] << " <arquivo_pedidos> <arquivo_historico>\n";
            cerr << "Exemplo: " << argv[0] << " pedidos.txt historico.txt\n";
            return 1;
        }
    return 0;
}


int contarLinhas(const char *nomeArquivo)
{
    std::ifstream arq(nomeArquivo);

    if (!arq)
        return -1;

    int linhas = 0;
    std::string linha;

    while (std::getline(arq, linha))
    {
        if (!linha.empty())
            linhas++;
    }

    return linhas;
}

int carregarPartidasListaContEst(
    const char *arquivo,
    ListaContEst *l,
    double *tempoListaContEst)
{
    std::ifstream arq(arquivo);

    if (!arq)
    {
        std::error_code erro;
        bool existe = std::filesystem::exists(arquivo, erro);

        if (!erro && !existe)
        {
            *tempoListaContEst = 0.0;
            return 0;
        }

        std::cerr << "Nao foi possivel abrir o historico.\n";
        return -1;
    }

    Jogador aux;
    std::string nome;
    int score;
    int qtePartidas = 0;

    Timer t;
    timer_iniciar(&t);

    while (std::getline(arq, nome) && arq >> score)
    {
        arq.ignore(
            std::numeric_limits<std::streamsize>::max(),
            '\n'
        );

        aux.nome_jogador = nome;
        aux.score = score;

        if (!nome.empty() && nome.back() == '\r')
            nome.pop_back();


        if (inserir(l, aux, tamanho(l)) == true)
        {
            qtePartidas++;
        } 
        else
        {
            std::cerr << "Erro ao inserir partida no historico.\n";
            *tempoListaContEst = timer_parar(&t);
            return -1;
        }
       
    }

    *tempoListaContEst = timer_parar(&t);

    return qtePartidas;
}