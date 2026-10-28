/* avl.cpp
 * Arvore AVL: BST com balanceamento automatico por rotacoes.
 * INF01203 - Estruturas de Dados - UFRGS
 */

#include <iostream>
#include <new>
#include "avl.hpp"

/* ------------------------------------------------------------------ */
/*  Auxiliares internos                                                 */
/* ------------------------------------------------------------------ */
static int maximo(int a, int b) { return a > b ? a : b; }

static NodoAvl *criarNodo(int dado, std::string receita) {
    NodoAvl *n = new (std::nothrow) NodoAvl;
    if (!n) return nullptr;
    n->dado = dado;
    n->receita = receita;
    n->altura = 0;
    n->esq    = nullptr;
    n->dir    = nullptr;
    return n;
}

static void atualizarAltura(NodoAvl *n) {
    if (n)
        n->altura = 1 + maximo(avlAltura(n->esq), avlAltura(n->dir));
}

/* ------------------------------------------------------------------ */
/*  Altura e fator de balanceamento                                     */
/* ------------------------------------------------------------------ */
int avlAltura(const NodoAvl *n) {
    return n ? n->altura : -1;
}

/* FB = h(esq) - h(dir). Positivo: pesado a esquerda. */
int avlFb(const NodoAvl *n) {
    return n ? avlAltura(n->esq) - avlAltura(n->dir) : 0;
}

/* ------------------------------------------------------------------ */
/*  Rotacoes simples                                                    */
/* ------------------------------------------------------------------ */

/*
 * Rotacao simples a direita (caso LL):
 *       y                x
 *      / \             /   \
 *     x   T3   ->    T1     y
 *    / \                   / \
 *   T1  T2               T2   T3
 */
static NodoAvl *rotDir(NodoAvl *y) {
    NodoAvl *x  = y->esq;
    NodoAvl *T2 = x->dir;
    x->dir = y;
    y->esq = T2;
    atualizarAltura(y);
    atualizarAltura(x);
    return x;
}

/*
 * Rotacao simples a esquerda (caso RR):
 *     x                  y
 *    / \               /   \
 *   T1   y    ->      x     T3
 *       / \          / \
 *      T2  T3       T1  T2
 */
static NodoAvl *rotEsq(NodoAvl *x) {
    NodoAvl *y  = x->dir;
    NodoAvl *T2 = y->esq;
    y->esq = x;
    x->dir = T2;
    atualizarAltura(x);
    atualizarAltura(y);
    return y;
}

/* ------------------------------------------------------------------ */
/*  Reequilibrio: detecta o caso e aplica a rotacao adequada           */
/* ------------------------------------------------------------------ */
static NodoAvl *reequilibrar(NodoAvl *raiz) {
    atualizarAltura(raiz);
    int fb = avlFb(raiz);

    /* Caso LL: pesado a esquerda, filho esquerdo tambem pesado a esq */
    if (fb > 1 && avlFb(raiz->esq) >= 0)
        return rotDir(raiz);

    /* Caso LR: pesado a esquerda, filho esquerdo pesado a dir */
    if (fb > 1 && avlFb(raiz->esq) < 0) {
        raiz->esq = rotEsq(raiz->esq);
        return rotDir(raiz);
    }

    /* Caso RR: pesado a direita, filho direito tambem pesado a dir */
    if (fb < -1 && avlFb(raiz->dir) <= 0)
        return rotEsq(raiz);

    /* Caso RL: pesado a direita, filho direito pesado a esq */
    if (fb < -1 && avlFb(raiz->dir) > 0) {
        raiz->dir = rotDir(raiz->dir);
        return rotEsq(raiz);
    }

    return raiz; /* ja balanceado */
}

/* ------------------------------------------------------------------ */
/*  Operacoes publicas                                                  */
/* ------------------------------------------------------------------ */
NodoAvl *avlBuscar(NodoAvl *raiz, int dado) {
    if (!raiz)             return nullptr;
    if (dado < raiz->dado) return avlBuscar(raiz->esq, dado);
    if (dado > raiz->dado) return avlBuscar(raiz->dir, dado);
    return raiz;
}

NodoAvl *avlInserir(NodoAvl *raiz, int dado, std::string receita) {
    if (!raiz) return criarNodo(dado, receita);
    if (dado < raiz->dado)
        raiz->esq = avlInserir(raiz->esq, dado, receita);
    else if (dado > raiz->dado)
        raiz->dir = avlInserir(raiz->dir, dado, receita);
    else
        return raiz; /* duplicatas ignoradas */
    return reequilibrar(raiz);
}

static NodoAvl *minimo(NodoAvl *n) {
    while (n->esq) n = n->esq;
    return n;
}

NodoAvl *avlRemover(NodoAvl *raiz, int dado) {
    if (!raiz) return nullptr;
    if (dado < raiz->dado) {
        raiz->esq = avlRemover(raiz->esq, dado);
    } else if (dado > raiz->dado) {
        raiz->dir = avlRemover(raiz->dir, dado);
    } else {
        /* Nodo encontrado */
        if (!raiz->esq || !raiz->dir) {
            NodoAvl *filho = raiz->esq ? raiz->esq : raiz->dir;
            delete raiz;
            return filho;
        }
        /* Dois filhos: substitui pelo menor da subarvore direita */
        NodoAvl *suc = minimo(raiz->dir);
        raiz->dado = suc->dado;
        raiz->dir  = avlRemover(raiz->dir, suc->dado);
    }
    return reequilibrar(raiz);
}

NodoAvl *avlDestruir(NodoAvl *raiz) {
    if (!raiz) return nullptr;
    avlDestruir(raiz->esq);
    avlDestruir(raiz->dir);
    delete raiz;
    return nullptr;
}

void avlEmOrdem(const NodoAvl *raiz) {
    if (!raiz) return;
    avlEmOrdem(raiz->esq);
    std::cout << raiz->dado << "(h" << raiz->altura << ") ";
    avlEmOrdem(raiz->dir);
}
