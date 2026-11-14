#ifndef LISTACONTEST_HPP
#define LISTACONTEST_HPP

#include "jogo.hpp"

constexpr int CAPACIDADE = 50;

struct ListaContEst {
    int tamanho;
    int capacidade;
    Jogador *dados;
};

void inicializar(ListaContEst *l);
int tamanho(const ListaContEst *l);
bool inserir(ListaContEst *l, Jogador novo, int pos);
Jogador acessar(const ListaContEst *l, int pos);
int buscar(const ListaContEst *l, int score);
bool remover(ListaContEst *l, int pos);
void destruir(ListaContEst *l);

void imprimir_ListaContEst(const ListaContEst *l);
int lista_para_vetor(ListaContEst *l, Jogador vetor[]);

double ordena_vetor_pelo_score_bubble_sort(
    Jogador vetor[], int tamanhoVetor
);

void imprime_dez_primeiros(Jogador vetor[]);
void imprime_de_1_a_9(Jogador vetor[], int tamanhoVetor);

#endif