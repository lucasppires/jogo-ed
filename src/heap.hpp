/* heap.hpp
 * heap maximo e fila de prioridade (max-heap sobre array)
 * inf01203 - Estruturas de Dados - UFRGS
 *
 * o heap e armazenado em um array com as seguintes relacoes de indice:
 *   pai(i)   = (i - 1) / 2
 *   esq(i)   = 2 * i + 1
 *   dir(i)   = 2 * i + 2
 */

#ifndef HEAP_HPP
#define HEAP_HPP

constexpr int HEAP_CAP = 1024;

/* ------------------------------------------------------------------ */
/*  heap sobre array (sem struct — funcoes de proposito geral)          */
/* ------------------------------------------------------------------ */

/* restaura a propriedade de heap descendo a partir do indice i */
void heapify(int a[], int n, int i);

/* restaura a propriedade de heap subindo a partir do indice i */
void siftUp(int a[], int i);

/* constroi um heap maximo in-place em O(n) */
void buildHeap(int a[], int n);

/* ordena 'a' em ordem crescente usando Heap Sort */
void heapSort(int a[], int n);

/* ------------------------------------------------------------------ */
/*  fila de prioridade (max-heap)                                       */
/* ------------------------------------------------------------------ */
struct FilaPrioridade {
    int dados[HEAP_CAP];
    int tamanho;
};

void fpInicializar(FilaPrioridade *fp);
bool fpEstaVazia(const FilaPrioridade *fp);
bool fpInserir(FilaPrioridade *fp, int valor);
bool fpMinimo(const FilaPrioridade *fp, int *valor);
bool fpRemoverMinimo(FilaPrioridade *fp, int *valor);

#endif /* heap_HPP */
