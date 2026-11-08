/* hash.cpp
 * Implementação do TAD Tabela Hash.
 * INF01203 — Estruturas de Dados — UFRGS
 */

#include <cmath>
#include "hash.hpp"

/* ================================================================
 * Funções de hash
 * ================================================================ */

int hashDivisao(int k, int m) {
    return k % m;
}

int hashMultiplicativo(int k, int m) {
    const double A = 0.6180339887;   /* (sqrt(5)-1)/2 — Knuth */
    double prod = static_cast<double>(k) * A;
    double frac = prod - std::floor(prod);
    return static_cast<int>(m * frac);
}

int hashString(const char *s, int m) {
    const int B = 31;
    int h = 0;
    for (int i = 0; s[i] != '\0'; i++)
        h = (h * B + static_cast<unsigned char>(s[i])) % m;
    return h;
}

/* ================================================================
 * Encadeamento separado
 * ================================================================ */

void encInicializar(TabelaEnc *t, int m) {
    t->m = m;
    t->n = 0;

    t->hits = 0;
    t->misses = 0;
    t->colisoes = 0;

    t->tabela = new No*[m];

    for (int i = 0; i < m; i++)
        t->tabela[i] = nullptr;
}

void encInserir(
    TabelaEnc *t,
    int chave,
    const Pedido *valor
) {
    int i = hashDivisao(chave, t->m);
    No *novo = new No;

    novo->chave = chave;
    novo->valor = valor;

    // Conta uma colisao se a posicao ja estiver ocupada.
    if (t->tabela[i] != nullptr) {
        t->colisoes++;
    }

    // Insere no inicio da lista dessa posicao.
    novo->prox = t->tabela[i];
    t->tabela[i] = novo;

    t->n++;
}

const Pedido *encBuscar(TabelaEnc *t, int chave)
{
    int i = hashDivisao(chave, t->m); 
    No *p = t->tabela[i];

    while (p != nullptr)
    {
        if (p->chave == chave) //vai analisando cada nodo da lista encadeada de tal posicao ate achar a chave procurada
        {
            t->hits++; // hits é o quando o pedido procurado está na hash
            return p->valor;
        }

        p = p->prox;
    }

    t->misses++; // misses é quando o pedido ainda nao esta na hash
    return nullptr;
}

bool encRemover(TabelaEnc *t, int chave) {
    int i   = hashDivisao(chave, t->m);
    No *p   = t->tabela[i];
    No *ant = nullptr;
    while (p != nullptr) {
        if (p->chave == chave) {
            if (ant == nullptr)
                t->tabela[i] = p->prox;
            else
                ant->prox = p->prox;
            delete p;
            t->n--;
            return true;
        }
        ant = p;
        p   = p->prox;
    }
    return false;
}

void encDestruir(TabelaEnc *t) {
    for (int i = 0; i < t->m; i++) {
        No *p = t->tabela[i];
        while (p) {
            No *prox = p->prox;
            delete p;
            p = prox;
        }
    }
    delete[] t->tabela;
    t->tabela = nullptr;
    t->m = t->n = 0;
}


void exibirEstatisticasHash(const TabelaEnc *cache)
{
    std::cout << "Estatísticas da tabela hash:\n";
    std::cout << "Tamanho da tabela: " << cache->m << "\n";
    std::cout << "Número de elementos: " << cache->n << "\n";
    std::cout << "Hits: " << cache->hits << "\n";
    std::cout << "Misses: " << cache->misses << "\n";
    std::cout << "Colisões: " << cache->colisoes << "\n";
    std::cout << "Fator de carga (n/m): " << static_cast<double>(cache->n) / cache->m << "\n"; //static_cast é pq o n e o m sao inteiros, entao transformamos o n em double para a divisao poder ter valores decimais
    
   double totalBuscas = static_cast<double>(cache->hits) + static_cast<double>(cache->misses);

    double taxaAcerto;

    if (totalBuscas > 0) 
    {
        taxaAcerto = 100.0 * static_cast<double>(cache->hits) / totalBuscas;
    } 
    else 
    {
        taxaAcerto = 0.0;
    }

    std::cout << "Taxa de acerto: " << taxaAcerto << "%\n";
}

/* ================================================================
 * Sondagem linear
 * ================================================================ */

void linInicializar(TabelaLinear *t, int m) {
    t->m      = m;
    t->n      = 0;
    t->tabela = new Slot[m];
    for (int i = 0; i < m; i++)
        t->tabela[i].estado = VAZIO;
}

bool linInserir(TabelaLinear *t, int chave, int valor) {
    int base    = chave % t->m;
    int pri_del = -1;
    for (int i = 0; i < t->m; i++) {
        int pos = (base + i) % t->m;
        if (t->tabela[pos].estado == VAZIO) {
            int dest;
            if (pri_del != -1)
                dest = pri_del;
            else
                dest = pos;
            t->tabela[dest].chave  = chave;
            t->tabela[dest].valor  = valor;
            t->tabela[dest].estado = OCUPADO;
            t->n++;
            return true;
        }
        if (t->tabela[pos].estado == DELETADO && pri_del == -1)
            pri_del = pos;
        if (t->tabela[pos].estado == OCUPADO && t->tabela[pos].chave == chave)
            return false;   /* chave duplicada */
    }
    if (pri_del != -1) {
        t->tabela[pri_del].chave  = chave;
        t->tabela[pri_del].valor  = valor;
        t->tabela[pri_del].estado = OCUPADO;
        t->n++;
        return true;
    }
    return false;   /* tabela cheia */
}

int linBuscar(const TabelaLinear *t, int chave) {
    int base = chave % t->m;
    for (int i = 0; i < t->m; i++) {
        int pos = (base + i) % t->m;
        if (t->tabela[pos].estado == VAZIO)
            return -1;
        if (t->tabela[pos].estado == OCUPADO && t->tabela[pos].chave == chave)
            return t->tabela[pos].valor;
    }
    return -1;
}

bool linRemover(TabelaLinear *t, int chave) {
    int base = chave % t->m;
    for (int i = 0; i < t->m; i++) {
        int pos = (base + i) % t->m;
        if (t->tabela[pos].estado == VAZIO)
            return false;
        if (t->tabela[pos].estado == OCUPADO && t->tabela[pos].chave == chave) {
            t->tabela[pos].estado = DELETADO;
            t->n--;
            return true;
        }
    }
    return false;
}

void linDestruir(TabelaLinear *t) {
    delete[] t->tabela;
    t->tabela = nullptr;
    t->m = t->n = 0;
}

/* ================================================================
 * Sondagem quadrática
 * ================================================================ */

void quadInicializar(TabelaQuad *t, int m) {
    t->m      = m;
    t->n      = 0;
    t->tabela = new Slot[m];
    for (int i = 0; i < m; i++)
        t->tabela[i].estado = VAZIO;
}

bool quadInserir(TabelaQuad *t, int chave, int valor) {
    int base    = chave % t->m;
    int pri_del = -1;
    for (int i = 0; i < t->m; i++) {
        int pos = (base + i * i) % t->m;
        if (t->tabela[pos].estado == VAZIO) {
            int dest;
            if (pri_del != -1)
                dest = pri_del;
            else
                dest = pos;
            t->tabela[dest].chave  = chave;
            t->tabela[dest].valor  = valor;
            t->tabela[dest].estado = OCUPADO;
            t->n++;
            return true;
        }
        if (t->tabela[pos].estado == DELETADO && pri_del == -1)
            pri_del = pos;
        if (t->tabela[pos].estado == OCUPADO && t->tabela[pos].chave == chave)
            return false;
    }
    if (pri_del != -1) {
        t->tabela[pri_del].chave  = chave;
        t->tabela[pri_del].valor  = valor;
        t->tabela[pri_del].estado = OCUPADO;
        t->n++;
        return true;
    }
    return false;
}

int quadBuscar(const TabelaQuad *t, int chave) {
    int base = chave % t->m;
    for (int i = 0; i < t->m; i++) {
        int pos = (base + i * i) % t->m;
        if (t->tabela[pos].estado == VAZIO)
            return -1;
        if (t->tabela[pos].estado == OCUPADO && t->tabela[pos].chave == chave)
            return t->tabela[pos].valor;
    }
    return -1;
}

bool quadRemover(TabelaQuad *t, int chave) {
    int base = chave % t->m;
    for (int i = 0; i < t->m; i++) {
        int pos = (base + i * i) % t->m;
        if (t->tabela[pos].estado == VAZIO)
            return false;
        if (t->tabela[pos].estado == OCUPADO && t->tabela[pos].chave == chave) {
            t->tabela[pos].estado = DELETADO;
            t->n--;
            return true;
        }
    }
    return false;
}

void quadDestruir(TabelaQuad *t) {
    delete[] t->tabela;
    t->tabela = nullptr;
    t->m = t->n = 0;
}

/* ================================================================
 * Hash duplo
 * ================================================================ */

void dblInicializar(TabelaDouble *t, int m) {
    t->m      = m;
    t->n      = 0;
    t->tabela = new Slot[m];
    for (int i = 0; i < m; i++)
        t->tabela[i].estado = VAZIO;
}

bool dblInserir(TabelaDouble *t, int chave, int valor) {
    int base    = chave % t->m;
    int passo   = 1 + (chave % (t->m - 2));
    int pri_del = -1;
    for (int i = 0; i < t->m; i++) {
        int pos = (base + i * passo) % t->m;
        if (t->tabela[pos].estado == VAZIO) {
            int dest;
            if (pri_del != -1)
                dest = pri_del;
            else
                dest = pos;
            t->tabela[dest].chave  = chave;
            t->tabela[dest].valor  = valor;
            t->tabela[dest].estado = OCUPADO;
            t->n++;
            return true;
        }
        if (t->tabela[pos].estado == DELETADO && pri_del == -1)
            pri_del = pos;
        if (t->tabela[pos].estado == OCUPADO && t->tabela[pos].chave == chave)
            return false;
    }
    if (pri_del != -1) {
        t->tabela[pri_del].chave  = chave;
        t->tabela[pri_del].valor  = valor;
        t->tabela[pri_del].estado = OCUPADO;
        t->n++;
        return true;
    }
    return false;
}

int dblBuscar(const TabelaDouble *t, int chave) {
    int base  = chave % t->m;
    int passo = 1 + (chave % (t->m - 2));
    for (int i = 0; i < t->m; i++) {
        int pos = (base + i * passo) % t->m;
        if (t->tabela[pos].estado == VAZIO)
            return -1;
        if (t->tabela[pos].estado == OCUPADO && t->tabela[pos].chave == chave)
            return t->tabela[pos].valor;
    }
    return -1;
}

bool dblRemover(TabelaDouble *t, int chave) {
    int base  = chave % t->m;
    int passo = 1 + (chave % (t->m - 2));
    for (int i = 0; i < t->m; i++) {
        int pos = (base + i * passo) % t->m;
        if (t->tabela[pos].estado == VAZIO)
            return false;
        if (t->tabela[pos].estado == OCUPADO && t->tabela[pos].chave == chave) {
            t->tabela[pos].estado = DELETADO;
            t->n--;
            return true;
        }
    }
    return false;
}

void dblDestruir(TabelaDouble *t) {
    delete[] t->tabela;
    t->tabela = nullptr;
    t->m = t->n = 0;
}
