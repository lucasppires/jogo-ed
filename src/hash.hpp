/* hash.hpp
 * tad Tabela Hash — funções de hash e tratamento de colisão
 * cobre o conteúdo das aulas 19 e 20 de INF01203 — UFRGS
 *
 */

#ifndef HASH_HPP
#define HASH_HPP

#include "pedido.hpp"
#include "medicoes.hpp"

/* ================================================================
 * funções de hash (aula 19)
 * ================================================================ */

/* hash por divisão: h(k) = k mod m
 * recomendação: m primo, não próximo de potência de 2 ou 10 */
int hashDivisao(int k, int m);

/* hash multiplicativo de Knuth: h(k) = floor(m * {k·A}), A ≈ 0,618
 * o caráter irracional de A espalha os índices uniformemente */
int hashMultiplicativo(int k, int m);

/* hash polinomial para strings via Regra de Horner, base B = 31
 * h₀ = 0,  hᵢ = hᵢ₋₁·B + s[i]  (mod m),  h(s) = h_L mod m */
int hashString(const char *s, int m);


/* ================================================================
 * encadeamento separado (aula 20)
 * ================================================================
 * cada slot é a cabeça de uma lista encadeada
 * suporta fator de carga λ > 1
 * custo médio de busca: O(1 + λ)
 */

struct No 
{
    int chave; //codigo do pedido, ex 1001
    const Pedido *valor;
    No *prox; //proximo no da lista em caso de colisao
};

struct TabelaEnc 
{
    No **tabela; //aponta para um vetor de listas encadeadas
    int m; //qtd de posicoes desse vetor
    int n; //quantidade de elementos inseridos na tabela
    unsigned long long hits; // pedido procurado esta na hash
    unsigned long long misses; // pedido nao esta na hash
    unsigned long long colisoes; // posicao ja ocupada na hash, entao temos que inserir na lista encadeada
};

void encInicializar(TabelaEnc *t, int m);
void encInserir(TabelaEnc *t, int chave, const Pedido *valor);
const Pedido *encBuscar(TabelaEnc *t, int chave);
bool encRemover(TabelaEnc *t, int chave);
void encDestruir(TabelaEnc *t);

void exibirEstatisticasHash(const TabelaEnc *cache, Metricas *met);


/* ================================================================
 * endereçamento aberto — tipo de slot compartilhado (aula 20)
 * ================================================================
 * remoção usa marca lápide (DELETADO) para não interromper sondagens
 */

enum EstadoSlot { VAZIO, OCUPADO, DELETADO };

struct Slot {
    int chave;
    int valor;
    EstadoSlot estado;
};


/* ================================================================
 * sondagem linear (aula 20)
 * ================================================================
 * pos(i) = (h(k) + i) mod m,  i = 0, 1, 2, …
 * vantagem: boa localidade de cache
 * desvantagem: agrupamento primário (clusters longos)
 * requer λ < 1; m primo recomendado
 */

struct TabelaLinear {
    Slot *tabela;
    int m;   /* número de slots (primo recomendado) */
    int n;   /* número de elementos */
};

void linInicializar(TabelaLinear *t, int m);
bool linInserir(TabelaLinear *t, int chave, int valor);
int linBuscar(const TabelaLinear *t, int chave);
bool linRemover(TabelaLinear *t, int chave);
void linDestruir(TabelaLinear *t);


/* ================================================================
 * sondagem quadrática (aula 20)
 * ================================================================
 * pos(i) = (h(k) + i²) mod m,  i = 0, 1, 2, …
 * elimina agrupamento primário; pode não visitar todos os slots
 * (garantido visitar pelo menos m/2 slots distintos se m é primo)
 * requer λ < 0,5 para garantia de inserção; m primo recomendado
 */

struct TabelaQuad {
    Slot *tabela;
    int m;   /* número de slots (primo recomendado) */
    int n;   /* número de elementos */
};

void quadInicializar(TabelaQuad *t, int m);
bool quadInserir(TabelaQuad *t, int chave, int valor);
int quadBuscar(const TabelaQuad *t, int chave);
bool quadRemover(TabelaQuad *t, int chave);
void quadDestruir(TabelaQuad *t);


/* ================================================================
 * hash duplo (aula 20)
 * ================================================================
 * pos(i) = (h1(k) + i·h2(k)) mod m,  i = 0, 1, 2, …
 * h1(k) = k mod m
 * h2(k) = 1 + (k mod (m-2))   — garante passo ≥ 1
 * elimina agrupamento secundário; melhor distribuição entre os três
 * requer m primo (e m-2 primo para máxima qualidade)
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

#endif/* hash_HPP */
