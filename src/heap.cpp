/* heap.cpp
 * Heap maximo e fila de prioridade (max-heap sobre array).
 * INF01203 - Estruturas de Dados - UFRGS
 */

#include "heap.hpp"

/* ------------------------------------------------------------------ */
/*  Auxiliar                                                            */
/* ------------------------------------------------------------------ */
static void trocar(int a[], int i, int j) {
    int tmp = a[i];
    a[i] = a[j];
    a[j] = tmp;
}

/* ------------------------------------------------------------------ */
/*  heapify (sift-down): desce o elemento em a[i] ate a posicao correta */
/*  Supoe que as subarvores esquerda e direita ja sao heaps validos.    */
/* ------------------------------------------------------------------ */
void heapify(int a[], int n, int i) {
    int maior = i;
    int esq   = 2 * i + 1;
    int dir   = 2 * i + 2;

    if (esq < n && a[esq] > a[maior]) maior = esq;
    if (dir < n && a[dir] > a[maior]) maior = dir;

    if (maior != i) {
        trocar(a, i, maior);
        heapify(a, n, maior);
    }
}

/* ------------------------------------------------------------------ */
/*  siftUp: sobe o elemento em a[i] ate a posicao correta.             */
/* ------------------------------------------------------------------ */
void siftUp(int a[], int i) {
    while (i > 0) {
        int pai = (i - 1) / 2;
        if (a[i] > a[pai]) {
            trocar(a, i, pai);
            i = pai;
        } else {
            break;
        }
    }
}

/* ------------------------------------------------------------------ */
/*  buildHeap: constroi um max-heap in-place em O(n).                  */
/*  Aplica heapify de baixo para cima, comecando no ultimo no interno. */
/* ------------------------------------------------------------------ */
void buildHeap(int a[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(a, n, i);
}

/* ------------------------------------------------------------------ */
/*  Heap Sort: ordena em ordem crescente.                               */
/*  1. buildHeap O(n)                                                   */
/*  2. n-1 vezes: troca a[0] (maximo) com o ultimo e heapify           */
/* ------------------------------------------------------------------ */
void heapSort(int a[], int n) {
    buildHeap(a, n);
    for (int i = n - 1; i > 0; i--) {
        trocar(a, 0, i);
        heapify(a, i, 0);
    }
}

/* ------------------------------------------------------------------ */
/*  Fila de prioridade                                                  */
/* ------------------------------------------------------------------ */
void fpInicializar(FilaPrioridade *fp) {
    fp->tamanho = 0;
}

bool fpEstaVazia(const FilaPrioridade *fp) {
    return fp->tamanho == 0;
}

bool fpInserir(FilaPrioridade *fp, int valor) {
    if (fp->tamanho >= HEAP_CAP) return false;
    fp->dados[fp->tamanho] = valor;
    siftUp(fp->dados, fp->tamanho);
    fp->tamanho++;
    return true;
}

bool fpMaximo(const FilaPrioridade *fp, int *valor) {
    if (fpEstaVazia(fp)) return false;
    *valor = fp->dados[0];
    return true;
}

bool fpRemoverMaximo(FilaPrioridade *fp, int *valor) {
    if (fpEstaVazia(fp)) return false;
    *valor = fp->dados[0];
    fp->tamanho--;
    fp->dados[0] = fp->dados[fp->tamanho];
    heapify(fp->dados, fp->tamanho, 0);
    return true;
}
