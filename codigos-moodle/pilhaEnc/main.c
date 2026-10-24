#include <stdio.h>
#include "pilhaEnc.h"

int main() {
    PilhaEnc p;
    Produto p1 = {1, "Produto A", 10.0f};
    Produto p2 = {2, "Produto B", 20.0f};
    Produto p3 = {3, "Produto C", 30.0f};
    Produto removido;

    inicializa(&p);

    empilha(&p, p1); // pilha: [A]
    empilha(&p, p2); // pilha: [A, B] (B no topo)
    empilha(&p, p3); // pilha: [A, B, C] (C no topo)

    printf("Tamanho: %d\n", tamanho(&p)); // imprime 3

    desempilha(&p, &removido);
    printf("Desempilhado: %s\n", removido.nome); // Produto C

    topo(&p, &removido);
    printf("Novo topo: %s\n", removido.nome); // Produto B

    while (!estaVazia(&p)) { // libera o restante da pilha, nodo a nodo
        desempilha(&p, &removido);
    }

    return 0;
}
