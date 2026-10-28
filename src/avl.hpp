/* avl.hpp
 * Arvore AVL: BST com balanceamento automatico por rotacoes.
 * INF01203 - Estruturas de Dados - UFRGS
 */

#ifndef AVL_HPP
#define AVL_HPP

/* ------------------------------------------------------------------ */
/*  Estrutura de um nodo AVL                                            */
/* ------------------------------------------------------------------ */
struct NodoAvl {
    int      dado;
    std::string receita;
    int      altura;
    NodoAvl *esq;
    NodoAvl *dir;
};

/* Altura e fator de balanceamento */
int      avlAltura(const NodoAvl *n);
int      avlFb(const NodoAvl *n);

/* Operacoes principais (retornam a nova raiz da subarvore) */
NodoAvl *avlBuscar(NodoAvl *raiz, int dado);
NodoAvl *avlInserir(NodoAvl *raiz, int dado, std::string receita);
NodoAvl *avlRemover(NodoAvl *raiz, int dado);
NodoAvl *avlDestruir(NodoAvl *raiz);

/* Caminhamento em-ordem (imprime em ordem crescente) */
void     avlEmOrdem(const NodoAvl *raiz);

#endif /* AVL_HPP */
