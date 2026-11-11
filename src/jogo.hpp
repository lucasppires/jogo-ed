#ifndef JOGO_HPP
#define JOGO_HPP

#include "avl.hpp"
#include "hash.hpp"
#include "heap.hpp"    // FilaPrioridade
#include "pilha.hpp"   // PilhaEnc


void novoJogo(NodoAvl *raiz, TabelaEnc *cache, int &estado_menu, char *argv[], PilhaEnc *p, FilaPrioridade *carnes, FilaPrioridade *ovos, FilaPrioridade *bacons, int turnoAtual, int quantidadesPereciveisDisponiveis[]);
const Pedido *obterPedido(NodoAvl *raiz, TabelaEnc *cache, int codigo);

const Pedido *sortearPedido(NodoAvl *raiz, TabelaEnc *cache);

int numero_aleatorio(int minimo, int maximo);

#endif