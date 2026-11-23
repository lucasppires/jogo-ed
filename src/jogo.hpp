#ifndef JOGO_HPP
#define JOGO_HPP

#include <string>

using namespace std;

#include "avl.hpp"
#include "hash.hpp"
#include "heap.hpp"    // filaPrioridade
#include "pilha.hpp"   // pilhaEnc


struct Jogador {
    string nome_jogador;
    int score;
};

typedef enum {
    FACIL = 1,
    NORMAL = 2,
    DIFICIL = 3
} DIFICULDADE; 

struct ListaContEst;   // declaração antecipada: definida em listacontest.hpp

void gravaJogoNoHistorico(int score, ListaContEst *lista_historico, const char* nomeArqHistorico);

void novoJogo(NodoAvl *raiz, TabelaEnc *cache, int &estado_menu, char *argv[], PilhaEnc *p, FilaPrioridade *carnes, FilaPrioridade *ovos, FilaPrioridade *bacons, int turnoAtual, int quantidadesPereciveisDisponiveis[], Jogador *player, Metricas &met, ListaContEst *lista_historico, int dificuldade);

const Pedido *obterPedido(NodoAvl *raiz, TabelaEnc *cache, int codigo, Metricas &met);

const Pedido *sortearPedido(NodoAvl *raiz, TabelaEnc *cache, Metricas &met);

int numero_aleatorio(int minimo, int maximo);

#endif