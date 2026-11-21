#ifndef SORTINGS_HPP
#define SORTINGS_HPP
#include "listacontest.hpp"

using namespace std;
#include <string>
#include <vector>

void merge(int a[], int aux[], int ini, int meio, int fim);
void mergeSortRec(int a[], int aux[], int ini, int fim);
void mergeSort(int a[], int n);

// adaptacoes
void mergeAdaptado(Jogador vetor[], Jogador aux[], int ini, int meio, int fim);
void mergeSortRecAdaptado(Jogador vetor[], Jogador aux[], int ini, int fim);
double mergeSortAdaptado(Jogador vetor[], int tamanhoVetor);   

int charAt(const string& s, int d);
void radixSortLSD(vector<string>& v);
double radixSortAdaptado(Jogador jogadores[], int tamanhoVetor);
void radixSortMSD(vector<string>& v, vector<string>& aux, int lo, int hi, int d);
void radixSortMSD(vector<string>& v);
void imprime(const vector<string>& v);

int particionar(int a[], int esq, int dir);
void quickSort(int a[], int esq, int dir);
int compararNomes(const string& a, const string& b);
int particionarAdaptado(Jogador vetor[], int esq, int dir);
void quickSortRecAdaptado(Jogador vetor[], int esq, int dir);
double quickSortAdaptado(Jogador vetor[], int tamanhoVetor);

#endif /* sortings_HPP */
