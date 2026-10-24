/* ordenacao.c
 * Algoritmos de ordenacao por comparacao: Bubble, Selection,
 * Insertion e Shell Sort.
 * INF01203 - Estruturas de Dados - UFRGS
 *
 * Compilar: gcc -Wall -o ordenacao ordenacao.c
 */

#include <stdio.h>

/* ------------------------------------------------------------------ */
/*  Auxiliar                                                            */
/* ------------------------------------------------------------------ */
static void trocar(int vetor[], int i, int j) {
    int tmp    = vetor[i];
    vetor[i]   = vetor[j];
    vetor[j]   = tmp;
}

static void imprimir(const int vetor[], int n) {
    printf("[");
    for (int i = 0; i < n; i++) {
        printf("%d", vetor[i]);
        if (i < n - 1) printf(", ");
    }
    printf("]\n");
}

/* ------------------------------------------------------------------ */
/*  Bubble Sort                                                         */
/* Compara pares adjacentes e troca se fora de ordem; repete ate       */
/* nenhuma troca ocorrer.                                              */
/* Complexidade: O(n) melhor caso, O(n^2) pior e medio caso           */
/* Estavel: sim. Em-lugar: sim.                                        */
/* ------------------------------------------------------------------ */
void bubbleSort(int vetor[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int trocou = 0;
        for (int j = 0; j < n - 1 - i; j++) {
            if (vetor[j] > vetor[j + 1]) {
                trocar(vetor, j, j + 1);
                trocou = 1;
            }
        }
        if (!trocou) break; /* vetor ja ordenado */
    }
}

/* ------------------------------------------------------------------ */
/*  Selection Sort                                                      */
/* Seleciona o menor elemento do sufixo nao-ordenado e o coloca na    */
/* posicao correta.                                                    */
/* Complexidade: O(n^2) em todos os casos                              */
/* Estavel: nao. Em-lugar: sim.                                        */
/* ------------------------------------------------------------------ */
void selectionSort(int vetor[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int iMin = i;
        for (int j = i + 1; j < n; j++) {
            if (vetor[j] < vetor[iMin])
                iMin = j;
        }
        if (iMin != i)
            trocar(vetor, i, iMin);
    }
}

/* ------------------------------------------------------------------ */
/*  Insertion Sort                                                      */
/* Insere cada elemento na posicao correta dentro do prefixo ja        */
/* ordenado, deslocando os maiores para a direita.                     */
/* Complexidade: O(n) melhor caso, O(n^2) pior e medio caso           */
/* Estavel: sim. Em-lugar: sim.                                        */
/* ------------------------------------------------------------------ */
void insertionSort(int vetor[], int n) {
    for (int i = 1; i < n; i++) {
        int chave = vetor[i];
        int j     = i - 1;
        while (j >= 0 && vetor[j] > chave) {
            vetor[j + 1] = vetor[j];
            j--;
        }
        vetor[j + 1] = chave;
    }
}

/* ------------------------------------------------------------------ */
/*  Shell Sort                                                          */
/* Generalizacao do Insertion Sort que usa um gap decrescente;         */
/* elementos distantes gap posicoes sao comparados e trocados,         */
/* ate gap = 1 (que e um Insertion Sort sobre vetor quase-ordenado).   */
/* Sequencia de gaps: n/2, n/4, ..., 1 (sequencia de Shell)           */
/* Complexidade: O(n^(3/2)) com essa sequencia (depende dos gaps)      */
/* Estavel: nao. Em-lugar: sim.                                        */
/* ------------------------------------------------------------------ */
void shellSort(int vetor[], int n) {
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            int chave = vetor[i];
            int j     = i - gap;
            while (j >= 0 && vetor[j] > chave) {
                vetor[j + gap] = vetor[j];
                j -= gap;
            }
            vetor[j + gap] = chave;
        }
    }
}

/* ------------------------------------------------------------------ */
/*  main de demonstracao                                                */
/* ------------------------------------------------------------------ */
static void copiar(const int src[], int dst[], int n) {
    for (int i = 0; i < n; i++) dst[i] = src[i];
}

int main(void) {
    int original[] = {64, 25, 12, 22, 11};
    int n = 5;
    int v[5];

    printf("Original:       "); imprimir(original, n);

    copiar(original, v, n); bubbleSort(v, n);
    printf("Bubble Sort:    "); imprimir(v, n);

    copiar(original, v, n); selectionSort(v, n);
    printf("Selection Sort: "); imprimir(v, n);

    copiar(original, v, n); insertionSort(v, n);
    printf("Insertion Sort: "); imprimir(v, n);

    copiar(original, v, n); shellSort(v, n);
    printf("Shell Sort:     "); imprimir(v, n);

    return 0;
}
