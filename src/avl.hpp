/* avl.hpp
 * arvore AVL: BST com balanceamento automatico por rotacoes
 * inf01203 - Estruturas de Dados - UFRGS
 */

#ifndef AVL_HPP
#define AVL_HPP
#include <string>
#include "pedido.hpp"

/* ------------------------------------------------------------------ */
/*  estrutura de um nodo AVL                                            */
/* ------------------------------------------------------------------ */

struct NodoAvl {
    Pedido  dado;
    int      altura;
    NodoAvl *esq;
    NodoAvl *dir;
};

/* altura e fator de balanceamento */
int      avlAltura(const NodoAvl *n);
int      avlFb(const NodoAvl *n);

/* operacoes principais (retornam a nova raiz da subarvore) */
NodoAvl *avlBuscar(NodoAvl *raiz, Pedido dado);
NodoAvl *buscarPorCodigo(NodoAvl *raiz, int codigo, int &comparacoes);
NodoAvl *avlInserir(NodoAvl *raiz, Pedido dado, int &rotacoes);
NodoAvl *avlRemover(NodoAvl *raiz, Pedido dado);
NodoAvl *avlDestruir(NodoAvl *raiz);

/* caminhamento em-ordem (imprime em ordem crescente) */
void     avlEmOrdem(const NodoAvl *raiz);



#endif /* avl_HPP */
