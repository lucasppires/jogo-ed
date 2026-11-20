#ifndef LEITURA_ARQUIVOS_HPP
#define LEITURA_ARQUIVOS_HPP

#include "avl.hpp"

using namespace std;
#include "listacontest.hpp"

int carregarPedidosAVL(
    const char *arquivo,
    NodoAvl **raiz,
    double *tempo,
    Metricas &met
);

int confere_argc_e_argv(int argc, char *argv[]);

int contarLinhas(const char *nomeArquivo);

int carregarPartidasListaContEst(
    const char *arquivo,
    ListaContEst *l,
    double *tempoListaContEst
);

bool montarReceita(const string &texto, ListaEnc *lista);

#endif
