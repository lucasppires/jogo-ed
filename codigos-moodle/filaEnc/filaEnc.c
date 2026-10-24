#include <stdio.h>
#include <stdlib.h>
#include "filaEnc.h"

void inicializa(FilaEnc *f) {
    f->frente = NULL;
    f->final = NULL;
}

int estaVazia(FilaEnc *f) {
    return f->frente == NULL;
}

int enfileira(FilaEnc *f, Produto valor) {
    Nodo *novo = (Nodo*) malloc(sizeof(Nodo));
    if (novo == NULL)
        return 0;

    novo->dado = valor;
    novo->prox = NULL;

    if (f->final != NULL)
        f->final->prox = novo; // o antigo final passa a apontar para o novo nodo
    else
        f->frente = novo;      // fila estava vazia: novo nodo também é a frente

    f->final = novo;
    return 1;
}

int desenfileira(FilaEnc *f, Produto *valorRemovido) {
    Nodo *removido;

    if (estaVazia(f)) // underflow
        return 0;

    removido = f->frente;
    *valorRemovido = removido->dado;
    f->frente = removido->prox;

    if (f->frente == NULL) // a fila ficou vazia
        f->final = NULL;

    free(removido);
    return 1;
}

int tamanho(FilaEnc *f) {
    Nodo *aux = f->frente;
    int contador = 0;

    while (aux != NULL) {
        contador++;
        aux = aux->prox;
    }

    return contador;
}
