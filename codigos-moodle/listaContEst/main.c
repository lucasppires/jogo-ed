#include <stdio.h>
#include "listaContEst.h"

int main() {
    ListaContEst l;
    int i;

    inicializar(&l);

    Produto p1 = {1, "Caneta", 2.50};
    Produto p2 = {2, "Caderno", 15.90};
    Produto p3 = {3, "Lapis", 1.20};

    inserir(&l, p1, 0); // lista: [Caneta]
    inserir(&l, p2, 1); // lista: [Caneta, Caderno]
    inserir(&l, p3, 1); // lista: [Caneta, Lapis, Caderno]

    printf("Lista (tamanho %d):\n", tamanho(&l));
    for (i = 0; i < tamanho(&l); i++) {
        Produto p = acessar(&l, i);
        printf("%d - %s - %.2f\n", p.cod, p.nome, p.preco);
    }

    printf("Posicao do produto de codigo 2: %d\n", buscar(&l, 2));

    remover(&l, 0); // remove "Caneta"
    printf("Apos remover a posicao 0, tamanho: %d\n", tamanho(&l));

    destruir(&l);
    return 0;
}
