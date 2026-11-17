#ifndef SORTINGS_HPP
#define SORTINGS_HPP
#include "listacontest.hpp"
#include <string>
#include <vector>

void merge(int a[], int aux[], int ini, int meio, int fim);
void mergeSortRec(int a[], int aux[], int ini, int fim);
void mergeSort(int a[], int n);

// ADAPTACOES
void mergeAdaptado(Jogador vetor[], Jogador aux[], int ini, int meio, int fim);
void mergeSortRecAdaptado(Jogador vetor[], Jogador aux[], int ini, int fim);
double mergeSortAdaptado(Jogador vetor[], int tamanhoVetor);   

int charAt(const std::string& s, int d);
void radixSortLSD(std::vector<std::string>& v);
double radixSortAdaptado(Jogador jogadores[], int tamanhoVetor);
void radixSortMSD(std::vector<std::string>& v, std::vector<std::string>& aux, int lo, int hi, int d);
void radixSortMSD(std::vector<std::string>& v);
void imprime(const std::vector<std::string>& v);

int particionar(int a[], int esq, int dir);
void quickSort(int a[], int esq, int dir);
int compararNomes(const string& a, const string& b);
int particionarAdaptado(Jogador vetor[], int esq, int dir);
void quickSortRecAdaptado(Jogador vetor[], int esq, int dir);
double quickSortAdaptado(Jogador vetor[], int tamanhoVetor);

#endif /* SORTINGS_HPP */
