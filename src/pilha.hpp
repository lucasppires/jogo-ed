#ifndef PILHA_HPP
#define PILHA_HPP

struct Produto {
    int   cod;
    char  nome[50];
    float preco;
};

struct Nodo {
    Nodo   *prox;
    Produto dado;
};

struct PilhaEnc {
    Nodo *topo;
};

void inicializa(PilhaEnc *p);
bool estaVazia(PilhaEnc *p);
bool empilha(PilhaEnc *p, Produto valor);
bool desempilha(PilhaEnc *p, Produto *valorRemovido);
bool topo(PilhaEnc *p, Produto *valor);
int  tamanho(PilhaEnc *p);

#endif /* PILHA_HPP */
