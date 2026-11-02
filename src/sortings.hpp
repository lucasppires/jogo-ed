#ifndef SORTINGS_HPP
#define SORTINGS_HPP
#include "listacontest.hpp"

void merge(int a[], int aux[], int ini, int meio, int fim);
void mergeSortRec(int a[], int aux[], int ini, int fim);
void mergeSort(int a[], int n);

// ADAPTACOES
void mergeAdaptado(Jogador vetor[], Jogador aux[], int ini, int meio, int fim);
void mergeSortRecAdaptado(Jogador vetor[], Jogador aux[], int ini, int fim);
double mergeSortAdaptado(Jogador vetor[], int tamanhoVetor);    

#endif /* SORTINGS_HPP */
