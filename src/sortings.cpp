#include <new>

using namespace std;
#include <cctype>
#include "sortings.hpp"
#include "timer.hpp"
#include "listacontest.hpp"

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
    int *aux = new (nothrow) int[n]; /* o vetor extra: O(n) de memoria */
    if (aux == nullptr) return;
    mergeSortRec(a, aux, 0, n - 1);
    delete[] aux;
}

// adaptacoes

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

    Jogador *aux = new (nothrow) Jogador[tamanhoVetor];
    if (aux == nullptr) return 0.0;

    mergeSortRecAdaptado(vetor, aux, 0, tamanhoVetor - 1);
    delete[] aux;

    double tempoExecucao = timer_parar(&t);
    return tempoExecucao;
}


// radix Sort para strings em C++
// duas versões:
//   1) lsd (Least Significant Digit): processa do último caractere para o primeiro
//      strings de tamanhos diferentes são tratadas como se fossem "completadas"
//      com um caractere de valor 0 no final (que vem antes de qualquer letra)
//   2) msd (Most Significant Digit): processa do primeiro caractere para o último,
//      de forma recursiva. Costuma ser mais eficiente para strings de tamanhos variados
//
// ambas usam counting sort (estável) em cada posição de caractere
// alfabeto: 256 símbolos (ASCII estendido) + 1 posição para "fim da string"
//
// compilar:  g++ -std=c++17 -Wall -O2 radix_sort_strings.cpp -o radix
// executar:  ./radix
 
#include <iostream>
#include <string>
#include <vector>
 
 
const int R = 256; // tamanho do alfabeto (ASCII estendido)
 
// retorna o "dígito" da string s na posição d
// se d passou do fim da string, retorna 0 (fim da string vem antes de qualquer caractere)
// caso contrário, retorna o código do caractere + 1 (faixa 1..256)
int charAt(const string& s, int d) {
    if (d < (int)s.size())
        return (unsigned char)s[d] + 1;
    return 0;
}
 
// =====================================================================
// 1) lsd Radix Sort
// complexidade: O(W * (n + R)), onde W = tamanho da maior string
// =====================================================================
void radixSortLSD(vector<string>& v) {
    int n = v.size();
    if (n <= 1) return;
 
    // descobre o tamanho da maior string
    int W = 0;
    for (const string& s : v)
        if ((int)s.size() > W) W = s.size();
 
    vector<string> aux(n);
 
    // counting sort estável em cada posição, da última para a primeira
    for (int d = W - 1; d >= 0; d--) {
        vector<int> count(R + 2, 0);
 
        // 1. conta a frequência de cada caractere na posição d
        for (int i = 0; i < n; i++)
            count[charAt(v[i], d) + 1]++;
 
        // 2. transforma contagens em posições iniciais (soma acumulada)
        for (int r = 0; r < R + 1; r++)
            count[r + 1] += count[r];
 
        // 3. distribui os elementos no vetor auxiliar (mantém a estabilidade)
        for (int i = 0; i < n; i++)
            aux[count[charAt(v[i], d)]++] = v[i];
 
        // 4. copia de volta
        for (int i = 0; i < n; i++)
            v[i] = aux[i];
    }
}

double radixSortAdaptado(Jogador jogadores[], int tamanhoVetor) {
    Timer t;
    timer_iniciar(&t);

    if (tamanhoVetor <= 1) return 0.0;

    // descobre o tamanho do maior nome
    int W = 0;
    for (int i = 0; i < tamanhoVetor; i++)
        if ((int)jogadores[i].nome_jogador.size() > W)
            W = jogadores[i].nome_jogador.size();

    Jogador *aux = new (nothrow) Jogador[tamanhoVetor];
    if (aux == nullptr) return 0.0;

    // feito por IA
    // igual ao charAt, mas converte a letra para minuscula antes,
    // para "ana" e "Ana" ficarem juntas e "Ze" nao vir antes de "ana"
    auto charAtMinusculo = [](const string& s, int d) {
        if (d < (int)s.size())
            return tolower((unsigned char)s[d]) + 1;
        return 0;
    };

    // counting sort estável em cada posição, da última para a primeira
    for (int d = W - 1; d >= 0; d--) {
        vector<int> count(R + 2, 0);

        // 1. conta a frequência de cada caractere na posição d
        for (int i = 0; i < tamanhoVetor; i++)
            count[charAtMinusculo(jogadores[i].nome_jogador, d) + 1]++;

        // 2. transforma contagens em posições iniciais (soma acumulada)
        for (int r = 0; r < R + 1; r++)
            count[r + 1] += count[r];

        // 3. distribui os jogadores no vetor auxiliar (mantém a estabilidade)
        for (int i = 0; i < tamanhoVetor; i++)
            aux[count[charAtMinusculo(jogadores[i].nome_jogador, d)]++] = jogadores[i];

        // 4. copia de volta
        for (int i = 0; i < tamanhoVetor; i++)
            jogadores[i] = aux[i];
    }

    delete[] aux;

    double tempoExecucao = timer_parar(&t);
    return tempoExecucao;
}
 
// =====================================================================
// 2) msd Radix Sort (recursivo)
// ordena v[lo..hi] olhando o caractere na posição d
// =====================================================================
void radixSortMSD(vector<string>& v, vector<string>& aux, int lo, int hi, int d) {
    if (hi <= lo) return;
 
    vector<int> count(R + 2, 0);
 
    // 1. conta a frequência
    for (int i = lo; i <= hi; i++)
        count[charAt(v[i], d) + 1]++;
 
    // 2. soma acumulada
    for (int r = 0; r < R + 1; r++)
        count[r + 1] += count[r];
 
    // 3. distribui
    for (int i = lo; i <= hi; i++)
        aux[count[charAt(v[i], d)]++] = v[i];
 
    // 4. copia de volta
    for (int i = lo; i <= hi; i++)
        v[i] = aux[i - lo];
 
    // 5. ordena recursivamente cada grupo que tem o mesmo caractere na posição d
    //    o grupo 0 (strings que já terminaram) não precisa ser ordenado de novo
    for (int r = 1; r <= R; r++)
        radixSortMSD(v, aux, lo + count[r - 1], lo + count[r] - 1, d + 1);
}
 
void radixSortMSD(vector<string>& v) {
    int n = v.size();
    if (n <= 1) return;
    vector<string> aux(n);
    radixSortMSD(v, aux, 0, n - 1, 0);
}
 
// =====================================================================
// teste
// =====================================================================
void imprime(const vector<string>& v) {
    for (const string& s : v)
        cout << s << " ";
    cout << "\n";
}

/*
int main() {
    vector<string> original = {
        "banana", "maca", "abacaxi", "uva", "manga", "kiwi",
        "melancia", "ameixa", "abacate", "mamao", "pera", "uva", "a", "ab"
    };

    cout << "Original:   ";
    imprime(original);

    vector<string> v1 = original;
    radixSortLSD(v1);
    cout << "LSD Radix:  ";
    imprime(v1);

    vector<string> v2 = original;
    radixSortMSD(v2);
    cout << "MSD Radix:  ";
    imprime(v2);

    return 0;
}
*/


// quick sort:

int particionar(int a[], int esq, int dir) {
    int pivo = a[dir];   /* x = A[b]: o último elemento é o pivô */
    int i = esq - 1;
    int j, tmp;

    for (j = esq; j < dir; j++) {
        if (a[j] <= pivo) {
            i++;
            tmp = a[i]; a[i] = a[j]; a[j] = tmp;   /* swap(A[i], A[j]) */
        }
    }
    tmp = a[i + 1]; a[i + 1] = a[dir]; a[dir] = tmp; /* pivô para a posição final */
    return i + 1;
}

void quickSort(int a[], int esq, int dir) {
    if (esq >= dir) return;              /* conquista: 0 ou 1 elemento */
    int p = particionar(a, esq, dir);    /* divisão: faz o trabalho */
    quickSort(a, esq, p - 1);
    quickSort(a, p + 1, dir);            /* recombinação: nada a fazer */
}

// feito por IA
// compara dois nomes ignorando maiusculas/minusculas (mesmo criterio do radix)
// retorna < 0 se a vem antes de b, 0 se sao iguais, > 0 se a vem depois de b
int compararNomes(const string& a, const string& b) {
    int n = (a.size() < b.size()) ? a.size() : b.size();
    for (int k = 0; k < n; k++) {
        int ca = tolower((unsigned char)a[k]);
        int cb = tolower((unsigned char)b[k]);
        if (ca != cb) return ca - cb;
    }
    return (int)a.size() - (int)b.size();   /* prefixo menor vem antes ("ab" < "abc") */
}

int particionarAdaptado(Jogador vetor[], int esq, int dir) {
    string pivo = vetor[dir].nome_jogador;   /* o último elemento é o pivô */
    int i = esq - 1;
    Jogador tmp;

    for (int j = esq; j < dir; j++) {
        // nomes que vem antes do pivo, ou iguais a ele, vao para a parte esquerda
        if (compararNomes(vetor[j].nome_jogador, pivo) <= 0) {
            i++;
            tmp = vetor[i]; vetor[i] = vetor[j]; vetor[j] = tmp;   /* swap(A[i], A[j]) */
        }
    }
    tmp = vetor[i + 1]; vetor[i + 1] = vetor[dir]; vetor[dir] = tmp; /* pivô para a posição final */
    return i + 1;
}

void quickSortRecAdaptado(Jogador vetor[], int esq, int dir) {
    if (esq >= dir) return;                          /* conquista: 0 ou 1 elemento */
    int p = particionarAdaptado(vetor, esq, dir);    /* divisão: faz o trabalho */
    // o pivo ja esta na posicao final, por isso as chamadas seguintes pulam seu indice
    quickSortRecAdaptado(vetor, esq, p - 1);
    quickSortRecAdaptado(vetor, p + 1, dir);         /* recombinação: nada a fazer */
}

double quickSortAdaptado(Jogador vetor[], int tamanhoVetor) {
    Timer t;
    timer_iniciar(&t);

    if (tamanhoVetor <= 1) return 0.0;

    quickSortRecAdaptado(vetor, 0, tamanhoVetor - 1);

    double tempoExecucao = timer_parar(&t);
    return tempoExecucao;
}

