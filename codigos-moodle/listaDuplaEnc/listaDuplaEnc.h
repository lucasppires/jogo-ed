#ifndef LISTADUPLAENC_H
#define LISTADUPLAENC_H

typedef struct {
    int cod;
    char nome[50];
    float preco;
} Produto;

typedef struct str_NodoD NodoD;

struct str_NodoD {
    NodoD *ant;
    NodoD *prox;
    Produto dado;
};

typedef struct {
    NodoD *ini;
    NodoD *fim;
} ListaDuplaEnc;

void    inicializar(ListaDuplaEnc *l);
void    imprimir(ListaDuplaEnc *l);
void    imprimirInverso(ListaDuplaEnc *l);
Produto acessar(ListaDuplaEnc *l, int cod);
int     inserirInicio(ListaDuplaEnc *l, Produto prod);
int     inserirFim(ListaDuplaEnc *l, Produto prod);
int     removerPorCod(ListaDuplaEnc *l, int cod);
void    destruir(ListaDuplaEnc *l);
int     tamanho(ListaDuplaEnc *l);

#endif
