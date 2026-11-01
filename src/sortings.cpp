#include <new>
#include "sortings.hpp"
#include "timer.hpp"
#include "lista.hpp"

void merge(int a[], int aux[], int ini, int meio, int fim) {
    for (int t = ini; t <= fim; t++)      /* linhas 1-2: copia para Aux */
        aux[t] = a[t];

    int i = ini, j = meio + 1, k = ini;   /* linhas 3-5 */

    while (i <= meio && j <= fim) {       /* linhas 6-12 */
        if (aux[i] <= aux[j])             /* <= (e nao <) mantem a estabilidade */
            a[k++] = aux[i++];
        else
            a[k++] = aux[j++];
    }
    while (i <= meio) a[k++] = aux[i++];  /* linhas 13-16 */
    while (j <= fim)  a[k++] = aux[j++];  /* linhas 17-20 */
}

void mergeSortRec(int a[], int aux[], int ini, int fim) {
    if (ini >= fim) return;               /* conquista: 0 ou 1 elemento */
    int meio = ini + (fim - ini) / 2;     /* divisao: ao meio */
    mergeSortRec(a, aux, ini, meio);
    mergeSortRec(a, aux, meio + 1, fim);
    merge(a, aux, ini, meio, fim);        /* recombinacao */
}

void mergeSort(int a[], int n) {
    if (n <= 1) return;
    int *aux = new (std::nothrow) int[n]; /* o vetor extra: O(n) de memoria */
    if (aux == nullptr) return;
    mergeSortRec(a, aux, 0, n - 1);
    delete[] aux;
}

// ADAPTACOES

void mergeAdaptado(Jogador vetor[], Jogador aux[], int ini, int meio, int fim) {
    for (int t = ini; t <= fim; t++)      /* linhas 1-2: copia para Aux */
        aux[t] = vetor[t];

    int i = ini, j = meio + 1, k = ini;   /* linhas 3-5 */

    while (i <= meio && j <= fim) {       /* linhas 6-12 */
        if (aux[i].score >= aux[j].score)             /* >= (e nao >) mantem a estabilidade */
            vetor[k++] = aux[i++];
        else
            vetor[k++] = aux[j++];
    }
    while (i <= meio) vetor[k++] = aux[i++];  /* linhas 13-16 */
    while (j <= fim)  vetor[k++] = aux[j++];  /* linhas 17-20 */
}

void mergeSortRecAdaptado(Jogador vetor[], Jogador aux[], int ini, int fim) {
    if (ini >= fim) return;               /* conquista: 0 ou 1 elemento */
    int meio = ini + (fim - ini) / 2;     /* divisao: ao meio */
    mergeSortRecAdaptado(vetor, aux, ini, meio);
    mergeSortRecAdaptado(vetor, aux, meio + 1, fim);
    mergeAdaptado(vetor, aux, ini, meio, fim);        /* recombinacao */
}

double mergeSortAdaptado(Jogador vetor[], int tamanhoVetor) {
    Timer t;
    timer_iniciar(&t);

    if (tamanhoVetor <= 1) return 0.0;

    Jogador *aux = new (std::nothrow) Jogador[tamanhoVetor];
    if (aux == nullptr) return 0.0;

    mergeSortRecAdaptado(vetor, aux, 0, tamanhoVetor - 1);
    delete[] aux;

    double tempoExecucao = timer_parar(&t);
    return tempoExecucao;
}
