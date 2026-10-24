#include <stdio.h>
#include "listaEnc.h"

int main() {
    ListaEnc lista;
    inicializar(&lista);

    Produto p1 = {1, "Produto A", 10.0f};
    Produto p2 = {2, "Produto B", 20.0f};

    inserirInicio(&lista, p1); // lista: [A]
    inserirFim(&lista, p2);    // lista: [A, B]

    imprimir(&lista);
    printf("Tamanho: %d\n", tamanho(&lista)); // imprime 2

    buscar(&lista, 1);

    removerPorCod(&lista, 1);  // lista: [B]
    destruir(&lista);          // lista: vazia, memória liberada

    return 0;
}
