/* heap.h
 * Heap maximo e fila de prioridade (max-heap sobre array).
 * INF01203 - Estruturas de Dados - UFRGS
 *
 * O heap e armazenado em um array com as seguintes relacoes de indice:
 *   pai(i)   = (i - 1) / 2
 *   esq(i)   = 2 * i + 1
 *   dir(i)   = 2 * i + 2
 */

#ifndef HEAP_H
#define HEAP_H

#define HEAP_CAP 1024

/* ------------------------------------------------------------------ */
/*  Heap sobre array (sem struct — funcoes de proposito geral)          */
/* ------------------------------------------------------------------ */

/* Restaura a propriedade de heap descendo a partir do indice i. */
void heapify(int a[], int n, int i);

/* Restaura a propriedade de heap subindo a partir do indice i. */
void siftUp(int a[], int i);

/* Constroi um heap maximo in-place em O(n). */
void buildHeap(int a[], int n);

/* Ordena 'a' em ordem crescente usando Heap Sort. */
void heapSort(int a[], int n);

/* ------------------------------------------------------------------ */
/*  Fila de prioridade (max-heap)                                       */
/* ------------------------------------------------------------------ */
typedef struct {
    int dados[HEAP_CAP];
    int tamanho;
} FilaPrioridade;

void fpInicializar(FilaPrioridade *fp);
int  fpEstaVazia(const FilaPrioridade *fp);
int  fpInserir(FilaPrioridade *fp, int valor);
int  fpMaximo(const FilaPrioridade *fp, int *valor);
int  fpRemoverMaximo(FilaPrioridade *fp, int *valor);

#endif /* HEAP_H */
