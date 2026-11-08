#ifndef JOGO_HPP
#define JOGO_HPP

#include "avl.hpp"
#include "hash.hpp"

void novoJogo(NodoAvl *raiz, int &estado_menu, char *argv[]);

const Pedido *obterPedido(NodoAvl *raiz, TabelaEnc *cache, int codigo);

int numero_aleatorio(int minimo, int maximo);

#endif