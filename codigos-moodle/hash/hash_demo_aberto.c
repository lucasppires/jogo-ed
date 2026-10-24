/* hash_demo_aberto.c
 * Demonstração: endereçamento aberto — linear, quadrático e hash duplo (aula 20).
 * INF01203 — Estruturas de Dados — UFRGS
 *
 * Compilar: gcc -Wall -o hash_demo_aberto hash_demo_aberto.c hash.c -lm
 */

#include <stdio.h>
#include <stdlib.h>
#include "hash.h"

int main(void) {

    /* --------------------------------------------------------
     * Sondagem linear (m = 11)
     * 22, 33, 44: todos têm h(k) = k % 11 = 0 — colisões garantidas.
     * Inserções ocupam slots 0, 1, 2 (sequência linear).
     * -------------------------------------------------------- */
    printf("=== Sondagem linear (m = 11) ===\n");

    TabelaLinear lin;
    linInicializar(&lin, 11);

    linInserir(&lin, 22, 220);   /* slot 0 */
    linInserir(&lin, 33, 330);   /* slot 1 (colisão, passo +1) */
    linInserir(&lin, 44, 440);   /* slot 2 (colisão, passo +1) */

    printf("buscar(22)  = %d\n", linBuscar(&lin, 22));   /* 220 */
    printf("buscar(33)  = %d\n", linBuscar(&lin, 33));   /* 330 */
    printf("buscar(44)  = %d\n", linBuscar(&lin, 44));   /* 440 */

    linRemover(&lin, 33);   /* marca slot 1 como DELETADO */
    printf("apos remover(33): buscar(33) = %d\n", linBuscar(&lin, 33));   /* -1 */
    printf("buscar(44) apos remover(33)  = %d\n", linBuscar(&lin, 44));   /* 440 — lapide nao interrompe */

    linDestruir(&lin);

    /* --------------------------------------------------------
     * Sondagem quadrática (m = 11)
     * 22, 33, 44: h(k) = 0.
     * i=0: slot 0; i=1: slot (0+1)=1; i=2: slot (0+4)=4; i=3: slot (0+9)=9.
     * -------------------------------------------------------- */
    printf("\n=== Sondagem quadratica (m = 11) ===\n");

    TabelaQuad quad;
    quadInicializar(&quad, 11);

    quadInserir(&quad, 22, 220);   /* slot 0 */
    quadInserir(&quad, 33, 330);   /* slot 1 */
    quadInserir(&quad, 44, 440);   /* slot 4 */

    printf("buscar(22)  = %d\n", quadBuscar(&quad, 22));   /* 220 */
    printf("buscar(33)  = %d\n", quadBuscar(&quad, 33));   /* 330 */
    printf("buscar(44)  = %d\n", quadBuscar(&quad, 44));   /* 440 */

    quadRemover(&quad, 33);
    printf("apos remover(33): buscar(33) = %d\n", quadBuscar(&quad, 33));   /* -1 */
    printf("buscar(44) apos remover(33)  = %d\n", quadBuscar(&quad, 44));   /* 440 */

    quadDestruir(&quad);

    /* --------------------------------------------------------
     * Hash duplo (m = 13)
     * 22: h1=9, h2=1+(22%11)=1.  slots 9, 10, 11, …
     * 35: h1=9, h2=1+(35%11)=2.  slots 9, 11, 0, …   (passo diferente)
     * 48: h1=9, h2=1+(48%11)=4.  slots 9, 0, 4, …
     * Cada chave usa seu próprio passo — sem agrupamento secundário.
     * -------------------------------------------------------- */
    printf("\n=== Hash duplo (m = 13) ===\n");

    TabelaDouble dbl;
    dblInicializar(&dbl, 13);

    dblInserir(&dbl, 22, 220);
    dblInserir(&dbl, 35, 350);
    dblInserir(&dbl, 48, 480);

    printf("buscar(22)  = %d\n", dblBuscar(&dbl, 22));   /* 220 */
    printf("buscar(35)  = %d\n", dblBuscar(&dbl, 35));   /* 350 */
    printf("buscar(48)  = %d\n", dblBuscar(&dbl, 48));   /* 480 */

    dblRemover(&dbl, 22);
    printf("apos remover(22): buscar(22) = %d\n", dblBuscar(&dbl, 22));   /* -1 */
    printf("buscar(35) apos remover(22)  = %d\n", dblBuscar(&dbl, 35));   /* 350 */

    dblDestruir(&dbl);
    return 0;
}
