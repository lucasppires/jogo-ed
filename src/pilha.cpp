#include <new>
#include "pilha.hpp"

void inicializa(PilhaEnc *p) {
    p->topo = nullptr;
}

bool estaVazia(PilhaEnc *p) {
    return p->topo == nullptr;
}

bool empilha(PilhaEnc *p, Produto valor) {
    Nodo *novo = new (std::nothrow) Nodo;
    if (novo == nullptr)
        return false;

    novo->dado = valor;
    novo->prox = p->topo; // aponta para o antigo topo
    p->topo = novo;       // o novo nodo passa a ser o topo
    return true;
}

bool desempilha(PilhaEnc *p, Produto *valorRemovido) {
    Nodo *removido;

    if (estaVazia(p)) // underflow
        return false;

    removido = p->topo;
    *valorRemovido = removido->dado;
    p->topo = removido->prox;
    delete removido;
    return true;
}

bool topo(PilhaEnc *p, Produto *valor) {
    if (estaVazia(p))
        return false;

    *valor = p->topo->dado;
    return true;
}

int tamanho(PilhaEnc *p) {
    Nodo *aux = p->topo;
    int contador = 0;

    while (aux != nullptr) {
        contador++;
        aux = aux->prox;
    }

    return contador;
}
