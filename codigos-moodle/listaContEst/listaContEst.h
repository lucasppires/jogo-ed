#ifndef LISTACONTEST_H
#define LISTACONTEST_H

#define CAPACIDADE 50

typedef struct {
    int cod;
    char nome[50];
    float preco;
} Produto;

typedef struct {
    int tamanho;
    Produto dados[CAPACIDADE];
} ListaContEst;

void inicializar(ListaContEst *l);
int tamanho(const ListaContEst *l);
int inserir(ListaContEst *l, Produto novo, int pos);
Produto acessar(const ListaContEst *l, int pos);
int buscar(const ListaContEst *l, int cod);
int remover(ListaContEst *l, int pos);
void destruir(ListaContEst *l);

#endif
