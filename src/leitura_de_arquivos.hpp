#ifndef LEITURA_ARQUIVOS_HPP
#define LEITURA_ARQUIVOS_HPP

#include "avl.hpp"
#include "listacontest.hpp"

int carregarPedidosAVL(
    const char *arquivo,
    NodoAvl **raiz,
    double *tempo
);

int confere_argc_e_argv(int argc, char *argv[]);

int contarLinhas(const char *nomeArquivo);

int carregarPartidasListaContEst(
    const char *arquivo,
    ListaContEst *l,
    double *tempoListaContEst
);

bool montarReceita(const std::string &texto, ListaEnc *lista);



#endif
