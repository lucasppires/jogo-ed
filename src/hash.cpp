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
    t->m      = m;
    t->n      = 0;
    t->tabela = new No*[m];
    for (int i = 0; i < m; i++)
        t->tabela[i] = nullptr;
}

void encInserir(TabelaEnc *t, int chave, int valor) {
    int i    = hashDivisao(chave, t->m);
    No *novo = new No;
    novo->chave  = chave;
    novo->valor  = valor;
    novo->prox   = t->tabela[i];
    t->tabela[i] = novo;
    t->n++;
}

int encBuscar(const TabelaEnc *t, int chave) {
    int i = hashDivisao(chave, t->m);
    No *p = t->tabela[i];
    while (p != nullptr) {
        if (p->chave == chave) return p->valor;
        p = p->prox;
    }
    return -1;
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
