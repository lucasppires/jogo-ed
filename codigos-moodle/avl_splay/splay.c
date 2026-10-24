/* splay.c
 * Splay Tree: BST com auto-ajuste por splaying.
 * INF01203 - Estruturas de Dados - UFRGS
 *
 * O splaying move o nodo acessado para a raiz usando combinacoes
 * de rotacoes: Zig, Zig-zig e Zig-zag.
 *
 * Compilar: gcc -Wall -o splay splay.c
 */

#include <stdio.h>
#include <stdlib.h>
#include "splay.h"

/* ------------------------------------------------------------------ */
/*  Auxiliares                                                          */
/* ------------------------------------------------------------------ */
static NodoSplay *criarNodo(int dado) {
    NodoSplay *n = (NodoSplay *) malloc(sizeof(NodoSplay));
    if (!n) return NULL;
    n->dado = dado;
    n->esq  = NULL;
    n->dir  = NULL;
    return n;
}

static NodoSplay *rotDir(NodoSplay *y) {
    NodoSplay *x = y->esq;
    y->esq = x->dir;
    x->dir = y;
    return x;
}

static NodoSplay *rotEsq(NodoSplay *x) {
    NodoSplay *y = x->dir;
    x->dir = y->esq;
    y->esq = x;
    return y;
}

/* ------------------------------------------------------------------ */
/*  Splay: move o nodo com 'dado' (ou o mais proximo) para a raiz.    */
/*  Implementacao top-down com no-auxiliar sentinela.                   */
/* ------------------------------------------------------------------ */
NodoSplay *splay(NodoSplay *raiz, int dado) {
    if (!raiz) return NULL;

    /* Sentinela: seus filhos esq/dir acumulam as subarvores esq/dir. */
    NodoSplay sentinela;
    sentinela.esq = sentinela.dir = NULL;

    NodoSplay *esqMax = &sentinela; /* maior nodo da subarvore esq   */
    NodoSplay *dirMin = &sentinela; /* menor nodo da subarvore dir   */

    while (1) {
        if (dado < raiz->dado) {
            if (!raiz->esq) break;
            /* Zig-zig a esquerda */
            if (dado < raiz->esq->dado) {
                raiz = rotDir(raiz);
                if (!raiz->esq) break;
            }
            /* Vincula raiz a subarvore direita */
            dirMin->esq = raiz;
            dirMin = raiz;
            raiz = raiz->esq;
        } else if (dado > raiz->dado) {
            if (!raiz->dir) break;
            /* Zig-zig a direita */
            if (dado > raiz->dir->dado) {
                raiz = rotEsq(raiz);
                if (!raiz->dir) break;
            }
            /* Vincula raiz a subarvore esquerda */
            esqMax->dir = raiz;
            esqMax = raiz;
            raiz = raiz->dir;
        } else {
            break;
        }
    }

    /* Reconecta as subarvores */
    esqMax->dir = raiz->esq;
    dirMin->esq = raiz->dir;
    raiz->esq   = sentinela.dir;
    raiz->dir   = sentinela.esq;
    return raiz;
}

/* ------------------------------------------------------------------ */
/*  Operacoes publicas                                                  */
/* ------------------------------------------------------------------ */

/* Busca: faz splay e verifica se a nova raiz e o elemento procurado. */
NodoSplay *splayBuscar(NodoSplay *raiz, int dado, NodoSplay **novaRaiz) {
    raiz = splay(raiz, dado);
    *novaRaiz = raiz;
    if (raiz && raiz->dado == dado) return raiz;
    return NULL;
}

NodoSplay *splayInserir(NodoSplay *raiz, int dado) {
    NodoSplay *n = criarNodo(dado);
    if (!n) return raiz;
    if (!raiz) return n;

    raiz = splay(raiz, dado);
    if (dado < raiz->dado) {
        n->esq    = raiz->esq;
        n->dir    = raiz;
        raiz->esq = NULL;
        return n;
    } else if (dado > raiz->dado) {
        n->dir    = raiz->dir;
        n->esq    = raiz;
        raiz->dir = NULL;
        return n;
    }
    free(n); /* duplicata */
    return raiz;
}

NodoSplay *splayRemover(NodoSplay *raiz, int dado) {
    if (!raiz) return NULL;
    raiz = splay(raiz, dado);
    if (raiz->dado != dado) return raiz; /* nao encontrado */

    NodoSplay *novo;
    if (!raiz->esq) {
        novo = raiz->dir;
    } else {
        /* Splay do maximo da subarvore esquerda */
        novo = splay(raiz->esq, dado);
        novo->dir = raiz->dir;
    }
    free(raiz);
    return novo;
}

NodoSplay *splayDestruir(NodoSplay *raiz) {
    if (!raiz) return NULL;
    splayDestruir(raiz->esq);
    splayDestruir(raiz->dir);
    free(raiz);
    return NULL;
}

void splayEmOrdem(const NodoSplay *raiz) {
    if (!raiz) return;
    splayEmOrdem(raiz->esq);
    printf("%d ", raiz->dado);
    splayEmOrdem(raiz->dir);
}

/* ------------------------------------------------------------------ */
/*  main de demonstracao                                                */
/* ------------------------------------------------------------------ */
int main(void) {
    NodoSplay *raiz = NULL;
    int chaves[] = {30, 20, 40, 10, 25, 35, 50};
    int n = 7;

    for (int i = 0; i < n; i++)
        raiz = splayInserir(raiz, chaves[i]);

    printf("Em-ordem apos insercoes: ");
    splayEmOrdem(raiz);
    printf("\n");

    /* Busca por 25 — deve trazer 25 para a raiz */
    NodoSplay *encontrado;
    splayBuscar(raiz, 25, &raiz);
    printf("Raiz apos buscar 25: %d\n", raiz->dado);

    raiz = splayRemover(raiz, 25);
    printf("Em-ordem apos remover 25: ");
    splayEmOrdem(raiz);
    printf("\n");

    raiz = splayDestruir(raiz);
    return 0;
}
