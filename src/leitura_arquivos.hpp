#ifndef LEITURA_ARQUIVOS_HPP
#define LEITURA_ARQUIVOS_HPP

#include "avl.hpp"
#include "lista.hpp"

int carregarPedidosAVL(
    const char *arquivo,
    NodoAvl **raiz,
    double *tempo
);

int contarLinhas(const char *nomeArquivo);

int carregarPartidasListaContEst(
    const char *arquivo,
    ListaContEst *l,
    double *tempoListaContEst
);

#endif