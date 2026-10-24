#ifndef LISTAENC_H
#define LISTAENC_H

typedef struct {
    int cod;
    char nome[50];
    float preco;
} Produto;

typedef struct str_Nodo Nodo;

struct str_Nodo {
    Nodo *prox;
    Produto dado;
};

typedef struct {
    Nodo *ini;
} ListaEnc;

void    inicializar(ListaEnc *lista);
void    imprimir(const ListaEnc *lista);
Produto buscar(const ListaEnc *lista, int cod);
int     inserirInicio(ListaEnc *lista, Produto prod);
int     inserirFim(ListaEnc *lista, Produto prod);
int     removerPorCod(ListaEnc *lista, int cod);
void    destruir(ListaEnc *lista);
int     tamanho(const ListaEnc *lista);

#endif
