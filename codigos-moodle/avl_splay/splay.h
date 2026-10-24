/* splay.h
 * Splay Tree: BST com auto-ajuste por splaying.
 * INF01203 - Estruturas de Dados - UFRGS
 */

#ifndef SPLAY_H
#define SPLAY_H

typedef struct NodoSplay {
    int               dado;
    struct NodoSplay *esq;
    struct NodoSplay *dir;
} NodoSplay;

/* Splay: move o nodo com 'dado' para a raiz (ou o mais proximo). */
NodoSplay *splay(NodoSplay *raiz, int dado);

NodoSplay *splayBuscar(NodoSplay *raiz, int dado, NodoSplay **novaRaiz);
NodoSplay *splayInserir(NodoSplay *raiz, int dado);
NodoSplay *splayRemover(NodoSplay *raiz, int dado);
NodoSplay *splayDestruir(NodoSplay *raiz);

void splayEmOrdem(const NodoSplay *raiz);

#endif /* SPLAY_H */
