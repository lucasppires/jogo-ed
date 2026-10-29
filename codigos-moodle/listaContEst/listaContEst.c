#include "listaContEst.h"

void inicializar(ListaContEst *l) {
    l->tamanho = 0;
}

int tamanho(const ListaContEst *l) {
    return l->tamanho;
}

int inserir(ListaContEst *l, Produto novo, int pos) {
    int i;

    if (l->tamanho == CAPACIDADE) return 0; // lista cheia
    if (pos > l->tamanho || pos < 0) return 0; // posição inválida

    for (i = l->tamanho; i > pos; i--) // abre espaço, empurrando para a direita
        l->dados[i] = l->dados[i - 1];

    l->dados[pos] = novo;
    l->tamanho++;
    return 1;
}

Produto acessar(const ListaContEst *l, int pos) {
    Produto pAux;
    if (pos >= l->tamanho || pos < 0) // posição inválida
        pAux.cod = -1;
    else
        pAux = l->dados[pos];

    return pAux;
}

int buscar(const ListaContEst *l, int cod) {
    int i;

    for (i = 0; i < l->tamanho; i++) {
        if (l->dados[i].cod == cod) {
            return i; // posição onde o produto foi encontrado
        }
    }

    return -1; // não encontrado
}

int remover(ListaContEst *l, int pos) {
    int i;

    if (pos >= l->tamanho || pos < 0) return 0; // posição inválida

    for (i = pos; i < l->tamanho - 1; i++) // puxa elementos seguintes para a esquerda
        l->dados[i] = l->dados[i + 1];

    l->tamanho--;
    return 1;
}

void destruir(ListaContEst *l) {
    l->tamanho = 0;
}
