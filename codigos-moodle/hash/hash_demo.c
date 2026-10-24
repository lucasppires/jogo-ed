/* hash_demo.c
 * Demonstração: funções de hash e encadeamento separado (aulas 19–20).
 * INF01203 — Estruturas de Dados — UFRGS
 *
 * Compilar: gcc -Wall -o hash_demo hash_demo.c hash.c -lm
 */

#include <stdio.h>
#include <stdlib.h>
#include "hash.h"

int main(void) {

    /* --------------------------------------------------------
     * Funções de hash (aula 19)
     * -------------------------------------------------------- */
    printf("=== Funcoes de hash (m = 13) ===\n");
    printf("hashDivisao(42, 13)          = %d\n", hashDivisao(42, 13));
    printf("hashDivisao(100, 13)         = %d\n", hashDivisao(100, 13));
    printf("hashMultiplicativo(42, 13)   = %d\n", hashMultiplicativo(42, 13));
    printf("hashString(\"gato\", 13)      = %d\n", hashString("gato", 13));
    printf("hashString(\"tago\", 13)      = %d\n", hashString("tago", 13));
    /* gato e tago são anagramas mas produzem índices diferentes */

    /* --------------------------------------------------------
     * Encadeamento separado (aula 20)
     * -------------------------------------------------------- */
    printf("\n=== Encadeamento separado (m = 7) ===\n");

    TabelaEnc enc;
    encInicializar(&enc, 7);

    int chaves[] = {10, 22, 31, 4, 15, 28, 17};
    for (int i = 0; i < 7; i++)
        encInserir(&enc, chaves[i], chaves[i]);

    printf("buscar(31)  = %d\n", encBuscar(&enc, 31));   /* 31 */
    printf("buscar(99)  = %d\n", encBuscar(&enc, 99));   /* -1 */
    printf("lambda      = %.2f\n", (double)enc.n / enc.m);

    encRemover(&enc, 31);
    printf("apos remover(31): buscar(31) = %d\n", encBuscar(&enc, 31));   /* -1 */

    encDestruir(&enc);
    return 0;
}
