#include <stdio.h>
#include <stdlib.h>
#include "pilhaEnc.h"

void inicializa(PilhaEnc *p) {
    p->topo = NULL;
}

int estaVazia(PilhaEnc *p) {
    return p->topo == NULL;
}

int empilha(PilhaEnc *p, Produto valor) {
    Nodo *novo = (Nodo*) malloc(sizeof(Nodo));
    if (novo == NULL)
        return 0;

    novo->dado = valor;
    novo->prox = p->topo; // aponta para o antigo topo
    p->topo = novo;        // o novo nodo passa a ser o topo
    return 1;
}

int desempilha(PilhaEnc *p, Produto *valorRemovido) {
    Nodo *removido;

    if (estaVazia(p)) // underflow
        return 0;

    removido = p->topo;
    *valorRemovido = removido->dado;
    p->topo = removido->prox;
    free(removido);
    return 1;
}

int topo(PilhaEnc *p, Produto *valor) {
    if (estaVazia(p))
        return 0;

    *valor = p->topo->dado;
    return 1;
}

int tamanho(PilhaEnc *p) {
    Nodo *aux = p->topo;
    int contador = 0;

    while (aux != NULL) {
        contador++;
        aux = aux->prox;
    }

    return contador;
}
