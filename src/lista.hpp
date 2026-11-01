#ifndef LISTA_HPP
#define LISTA_HPP
#include <string>

struct Produto {
    int   cod;
    char  nome[50];
    float preco;
};

struct Jogador {
    std :: string nome_jogador;
    int score;
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
    int    capacidade;
    Jogador *dados;
};

void    inicializar(ListaContEst *l);
int     tamanho(const ListaContEst *l);
bool    inserir(ListaContEst *l, Jogador novo, int pos);
Jogador acessar(const ListaContEst *l, int pos);
int     buscar(const ListaContEst *l, int cod);
bool    remover(ListaContEst *l, int pos);
void    destruir(ListaContEst *l);
void    imprimir_ListaContEst(const ListaContEst *l);
int lista_para_vetor(ListaContEst *l, Jogador vetor[]);
double ordena_vetor_pelo_score_bubble_sort(Jogador vetor[], int tamanhoVetor);
double mergeSortAdaptado(Jogador vetor[], int tamanhoVetor);
void imprime_dez_primeiros(Jogador vetor[]);

#endif /* LISTA_HPP */