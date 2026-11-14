#ifndef JOGO_HPP
#define JOGO_HPP

#include <string>

#include "avl.hpp"
#include "hash.hpp"
#include "heap.hpp"    // FilaPrioridade
#include "pilha.hpp"   // PilhaEnc


struct Jogador {
    std::string nome_jogador;
    int score;
};

void novoJogo(NodoAvl *raiz, TabelaEnc *cache, int &estado_menu, char *argv[], PilhaEnc *p, FilaPrioridade *carnes, FilaPrioridade *ovos, FilaPrioridade *bacons, int turnoAtual, int quantidadesPereciveisDisponiveis[], Jogador *player);
const Pedido *obterPedido(NodoAvl *raiz, TabelaEnc *cache, int codigo);

const Pedido *sortearPedido(NodoAvl *raiz, TabelaEnc *cache);

int numero_aleatorio(int minimo, int maximo);

#endif