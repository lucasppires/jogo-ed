#ifndef LEITURA_ARQUIVOS_HPP
#define LEITURA_ARQUIVOS_HPP

#include "avl.hpp"
#include "lista.hpp"

// Função que retorna o total de pedidos (Código (números) e Receita (string) ) e os põe na AVL
int carregarPedidosAVL(const char *arquivo, NodoAvl **raiz, double *tempo);

int contarLinhas(const char *nomeArquivo);

int carregarPartidasListaContEst(const char *arquivo, ListaContEst *l, double *tempoListaContEst);

#endif /* LEITURA_arquivos_HPP */