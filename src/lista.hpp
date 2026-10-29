#ifndef LISTA_HPP
#define LISTA_HPP

struct Produto {
    int   cod;
    char  nome[50];
    float preco;
};

struct NodoD {
    NodoD  *ant;
    NodoD  *prox;
    Produto dado;
};

struct ListaDuplaEnc {
    NodoD *ini;
    NodoD *fim;
};

void    inicializar(ListaDuplaEnc *l);
void    imprimir(ListaDuplaEnc *l);
void    imprimirInverso(ListaDuplaEnc *l);
Produto acessar(ListaDuplaEnc *l, int cod);
bool    inserirInicio(ListaDuplaEnc *l, Produto prod);
bool    inserirFim(ListaDuplaEnc *l, Produto prod);
bool    removerPorCod(ListaDuplaEnc *l, int cod);
void    destruir(ListaDuplaEnc *l);
int     tamanho(ListaDuplaEnc *l);


constexpr int CAPACIDADE = 50;

struct ListaContEst {
    int     tamanho;
    Produto dados[CAPACIDADE];
};

void    inicializar(ListaContEst *l);
int     tamanho(const ListaContEst *l);
bool    inserir(ListaContEst *l, Produto novo, int pos);
Produto acessar(const ListaContEst *l, int pos);
int     buscar(const ListaContEst *l, int cod);
bool    remover(ListaContEst *l, int pos);
void    destruir(ListaContEst *l);

#endif /* LISTA_HPP */