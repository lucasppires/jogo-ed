/* hash.hpp
 * TAD Tabela Hash — funções de hash e tratamento de colisão.
 * Cobre o conteúdo das aulas 19 e 20 de INF01203 — UFRGS.
 *
 */

#ifndef HASH_HPP
#define HASH_HPP

/* ================================================================
 * Funções de hash (aula 19)
 * ================================================================ */

/* Hash por divisão: h(k) = k mod m
 * Recomendação: m primo, não próximo de potência de 2 ou 10. */
int hashDivisao(int k, int m);

/* Hash multiplicativo de Knuth: h(k) = floor(m * {k·A}), A ≈ 0,618.
 * O caráter irracional de A espalha os índices uniformemente. */
int hashMultiplicativo(int k, int m);

/* Hash polinomial para strings via Regra de Horner, base B = 31.
 * h₀ = 0,  hᵢ = hᵢ₋₁·B + s[i]  (mod m),  h(s) = h_L mod m */
int hashString(const char *s, int m);


/* ================================================================
 * Encadeamento separado (aula 20)
 * ================================================================
 * Cada slot é a cabeça de uma lista encadeada.
 * Suporta fator de carga λ > 1.
 * Custo médio de busca: O(1 + λ).
 */

struct No {
    int chave;
    int valor;
    No *prox;
};

struct TabelaEnc {
    No **tabela;   /* vetor de ponteiros para listas */
    int m;         /* número de slots */
    int n;         /* número de elementos */
};

void encInicializar(TabelaEnc *t, int m);
void encInserir(TabelaEnc *t, int chave, int valor);
int  encBuscar(const TabelaEnc *t, int chave);
bool encRemover(TabelaEnc *t, int chave);
void encDestruir(TabelaEnc *t);


/* ================================================================
 * Endereçamento aberto — tipo de slot compartilhado (aula 20)
 * ================================================================
 * Remoção usa marca lápide (DELETADO) para não interromper sondagens.
 */

enum EstadoSlot { VAZIO, OCUPADO, DELETADO };

struct Slot {
    int chave;
    int valor;
    EstadoSlot estado;
};


/* ================================================================
 * Sondagem linear (aula 20)
 * ================================================================
 * pos(i) = (h(k) + i) mod m,  i = 0, 1, 2, …
 * Vantagem: boa localidade de cache.
 * Desvantagem: agrupamento primário (clusters longos).
 * Requer λ < 1; m primo recomendado.
 */

struct TabelaLinear {
    Slot *tabela;
    int m;   /* número de slots (primo recomendado) */
    int n;   /* número de elementos */
};

void linInicializar(TabelaLinear *t, int m);
bool linInserir(TabelaLinear *t, int chave, int valor);
int  linBuscar(const TabelaLinear *t, int chave);
bool linRemover(TabelaLinear *t, int chave);
void linDestruir(TabelaLinear *t);


/* ================================================================
 * Sondagem quadrática (aula 20)
 * ================================================================
 * pos(i) = (h(k) + i²) mod m,  i = 0, 1, 2, …
 * Elimina agrupamento primário; pode não visitar todos os slots
 * (garantido visitar pelo menos m/2 slots distintos se m é primo).
 * Requer λ < 0,5 para garantia de inserção; m primo recomendado.
 */

struct TabelaQuad {
    Slot *tabela;
    int m;   /* número de slots (primo recomendado) */
    int n;   /* número de elementos */
};

void quadInicializar(TabelaQuad *t, int m);
bool quadInserir(TabelaQuad *t, int chave, int valor);
int  quadBuscar(const TabelaQuad *t, int chave);
bool quadRemover(TabelaQuad *t, int chave);
void quadDestruir(TabelaQuad *t);


/* ================================================================
 * Hash duplo (aula 20)
 * ================================================================
 * pos(i) = (h1(k) + i·h2(k)) mod m,  i = 0, 1, 2, …
 * h1(k) = k mod m
 * h2(k) = 1 + (k mod (m-2))   — garante passo ≥ 1
 * Elimina agrupamento secundário; melhor distribuição entre os três.
 * Requer m primo (e m-2 primo para máxima qualidade).
 */

struct TabelaDouble {
    Slot *tabela;
    int m;   /* número de slots (primo recomendado, e m-2 primo) */
    int n;   /* número de elementos */
};

void dblInicializar(TabelaDouble *t, int m);
bool dblInserir(TabelaDouble *t, int chave, int valor);
int  dblBuscar(const TabelaDouble *t, int chave);
bool dblRemover(TabelaDouble *t, int chave);
void dblDestruir(TabelaDouble *t);

#endif /* HASH_HPP */
