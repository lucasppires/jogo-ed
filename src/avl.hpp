/* avl.hpp
 * Arvore AVL: BST com balanceamento automatico por rotacoes.
 * INF01203 - Estruturas de Dados - UFRGS
 */

#ifndef AVL_HPP
#define AVL_HPP
#include <string>
#include "pedido.hpp"

/* ------------------------------------------------------------------ */
/*  Estrutura de um nodo AVL                                            */
/* ------------------------------------------------------------------ */

struct NodoAvl {
    Pedido  dado;
    int      altura;
    NodoAvl *esq;
    NodoAvl *dir;
};

/* Altura e fator de balanceamento */
int      avlAltura(const NodoAvl *n);
int      avlFb(const NodoAvl *n);

/* Operacoes principais (retornam a nova raiz da subarvore) */
NodoAvl *avlBuscar(NodoAvl *raiz, Pedido dado);
NodoAvl *buscarPorCodigo(NodoAvl *raiz, int codigo);
NodoAvl *avlInserir(NodoAvl *raiz, Pedido dado);
NodoAvl *avlRemover(NodoAvl *raiz, Pedido dado);
NodoAvl *avlDestruir(NodoAvl *raiz);

/* Caminhamento em-ordem (imprime em ordem crescente) */
void     avlEmOrdem(const NodoAvl *raiz);



#endif /* AVL_HPP */
