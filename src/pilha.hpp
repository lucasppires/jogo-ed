#ifndef PILHA_HPP
#define PILHA_HPP
#include "ingredientes.hpp"

struct Produto {
    int   cod;
    char  nome[50];
    float preco;
};

struct Nodo {
    Nodo   *prox;
    Ingrediente dado;
};

struct PilhaEnc {
    Nodo *topo;
};

void inicializa(PilhaEnc *p);
bool estaVazia(PilhaEnc *p);
bool empilha(PilhaEnc *p, Ingrediente adicionado);
bool desempilha(PilhaEnc *p, Ingrediente *removido);
bool topo(PilhaEnc *p, Ingrediente *valor);
int  tamanho(PilhaEnc *p);
void esvaziarPilha(PilhaEnc *p);
void montarPilhaViaSimbolos(PilhaEnc *p, const char *simbolos);

#endif /* PILHA_HPP */