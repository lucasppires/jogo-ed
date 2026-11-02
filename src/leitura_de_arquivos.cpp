#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <filesystem>
#include <system_error>

#include "avl.hpp"
#include "listacontest.hpp"
#include "timer.hpp"
#include "leitura_de_arquivos.hpp"

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

    while (arq >> codigo >> receita) //le o código e a receita do pedido 
    {
        Pedido pedido{};  //{} inicializa os campos com valores nulos, no caso 0 e nullptr
        pedido.cod = codigo;

        if (avlBuscar(*raiz, pedido) != nullptr) //verifica se o código do pedido já existe na árvore
        {
            qtePedidosLidos++;
            continue; //quebra o loop e passa para o próximo pedido, pois o código já existe na árvore
        }

        // Comeca com a lista vazia.
        inicializar(&pedido.receita);

        // Transforma cada letra do texto em um no da lista.
        if (!montarReceita(receita, &pedido.receita)) 
        {
            *tempo = timer_parar(&t); //se der erro na montagem da receita, para o timer e retorna -1
            return -1;
        }

        *raiz = avlInserir(*raiz, pedido);  //insere o pedido na árvore AVL

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

bool montarReceita(const std::string &texto, ListaEnc *lista) 
{
    for (char simbolo : texto) //percorre cada caractere da string de receita
    {
        const Ingrediente *ingrediente = buscarIngrediente(simbolo);  //analisa o simbolo e busca o ingrediente correspondente

        if (ingrediente == nullptr)  //se o ingrediente for invalido ou nao for encontrado
        {
            std::cerr << "Ingrediente desconhecido: " << simbolo << std::endl;
            destruir(lista);  //destrói a lista para evitar vazamento de memória
            return false;
        }
        else //se o ingrediente for valido, insere no final da lista
        {
            if (!inserirFim(lista, *ingrediente)) //se der erro na inserção
            {
                std::cerr << "Erro ao inserir ingrediente na lista.\n";
                destruir(lista);
                return false;
            }
        }

    }

    return true;
}
