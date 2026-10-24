#include <stdio.h>
#include "listaDuplaEnc.h"

int main() {
    ListaDuplaEnc l;
    inicializar(&l);

    Produto p1 = {1, "Produto A", 10.0f};
    Produto p2 = {2, "Produto B", 20.0f};
    Produto p3 = {3, "Produto C", 30.0f};

    inserirInicio(&l, p1); // lista: [A]
    inserirFim(&l, p2);    // lista: [A, B]
    inserirFim(&l, p3);    // lista: [A, B, C]

    printf("Lista (frente para tras):\n");
    imprimir(&l);

    printf("Lista (tras para frente):\n");
    imprimirInverso(&l);

    printf("Tamanho: %d\n", tamanho(&l)); // imprime 3

    acessar(&l, 2);

    removerPorCod(&l, 2); // lista: [A, C]
    destruir(&l);         // lista: vazia, memória liberada

    return 0;
}
