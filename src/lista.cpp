


#include <iostream>
#include <iomanip>
#include <new>
#include "lista.hpp"

/* Imprime um produto no formato "cod - nome - preco" (preco com 2 casas),
 * sem alterar a formatacao de std::cout para o resto do programa. */
static void imprimirProduto(const Produto &p) {
    std::ios_base::fmtflags flags = std::cout.flags();
    std::streamsize precisao = std::cout.precision();

    std::cout << p.cod << " - " << p.nome << " - "
              << std::fixed << std::setprecision(2) << p.preco << '\n';

    std::cout.flags(flags);
    std::cout.precision(precisao);
}

void inicializar(ListaDuplaEnc *l) {
    l->ini = nullptr;
    l->fim = nullptr;
}

void imprimir(ListaDuplaEnc *l) {
    NodoD *aux = l->ini;

    while (aux != nullptr) {
        imprimirProduto(aux->dado);
        aux = aux->prox;
    }
}

void imprimirInverso(ListaDuplaEnc *l) {
    NodoD *aux = l->fim;

    while (aux != nullptr) {
        imprimirProduto(aux->dado);
        aux = aux->ant;
    }
}

Produto acessar(ListaDuplaEnc *l, int cod) {
    NodoD *aux = l->ini;
    Produto prod = {-1, "", 0.0f};

    while (aux != nullptr) {
        if (aux->dado.cod == cod)
            return aux->dado;
        aux = aux->prox;
    }

    return prod;
}

bool inserirInicio(ListaDuplaEnc *l, Produto prod) {
    NodoD *novo = new (std::nothrow) NodoD;
    if (novo == nullptr)
        return false;

    novo->dado = prod;
    novo->ant  = nullptr;
    novo->prox = l->ini;

    if (l->ini != nullptr)
        l->ini->ant = novo; // o antigo início passa a ter um antecessor
    else
        l->fim = novo;      // lista estava vazia: novo nodo também é o fim

    l->ini = novo;
    return true;
}

bool inserirFim(ListaDuplaEnc *l, Produto prod) {
    NodoD *novo = new (std::nothrow) NodoD;
    if (novo == nullptr)
        return false;

    novo->dado = prod;
    novo->prox = nullptr;
    novo->ant  = l->fim;

    if (l->fim != nullptr)
        l->fim->prox = novo; // o antigo fim passa a apontar para o novo nodo
    else
        l->ini = novo;       // lista estava vazia: novo nodo também é o início

    l->fim = novo;
    return true;
}

bool removerPorCod(ListaDuplaEnc *l, int cod) {
    NodoD *aux = l->ini;

    while (aux != nullptr && aux->dado.cod != cod)
        aux = aux->prox;

    if (aux == nullptr) // não encontrado
        return false;

    if (aux->ant != nullptr) // existe antecessor: religa por ele
        aux->ant->prox = aux->prox;
    else                     // removendo o próprio início
        l->ini = aux->prox;

    if (aux->prox != nullptr) // existe sucessor: religa por ele
        aux->prox->ant = aux->ant;
    else                      // removendo o próprio fim
        l->fim = aux->ant;

    delete aux;
    return true;
}

void destruir(ListaDuplaEnc *l) {
    NodoD *ant;
    NodoD *aux = l->ini;

    while (aux != nullptr) {
        ant = aux;
        aux = aux->prox;
        delete ant;
    }

    l->ini = nullptr;
    l->fim = nullptr;
}

int tamanho(ListaDuplaEnc *l) {
    NodoD *aux = l->ini;
    int contador = 0;

    while (aux != nullptr) {
        contador++;
        aux = aux->prox;
    }

    return contador;
}


void inicializar(ListaContEst *l) {
    l->tamanho = 0;
}

int tamanho(const ListaContEst *l) {
    return l->tamanho;
}

bool inserir(ListaContEst *l, Produto novo, int pos) {
    if (l->tamanho == CAPACIDADE) return false;       // lista cheia
    if (pos > l->tamanho || pos < 0) return false;    // posição inválida

    for (int i = l->tamanho; i > pos; i--) // abre espaço, empurrando para a direita
        l->dados[i] = l->dados[i - 1];

    l->dados[pos] = novo;
    l->tamanho++;
    return true;
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
    for (int i = 0; i < l->tamanho; i++) {
        if (l->dados[i].cod == cod) {
            return i; // posição onde o produto foi encontrado
        }
    }

    return -1; // não encontrado
}

bool remover(ListaContEst *l, int pos) {
    if (pos >= l->tamanho || pos < 0) return false; // posição inválida

    for (int i = pos; i < l->tamanho - 1; i++) // puxa elementos seguintes para a esquerda
        l->dados[i] = l->dados[i + 1];

    l->tamanho--;
    return true;
}

void destruir(ListaContEst *l) {
    l->tamanho = 0;
}