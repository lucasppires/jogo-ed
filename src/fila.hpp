#ifndef FILA_HPP
#define FILA_HPP

#include "pedido.hpp"

struct Nodo {
    Nodo   *prox;
    Cliente dado;
};

struct FilaEnc {
    Nodo *frente;
    Nodo *final;
};

void inicializa(FilaEnc *f);
bool estaVazia(FilaEnc *f);
bool enfileira(FilaEnc *f, Cliente valor);
bool desenfileira(FilaEnc *f, Cliente *valorRemovido);
int  tamanho(FilaEnc *f);
void destruir(FilaEnc *fila);

Cliente criarCliente(int index, int pacienciaInicial, const Pedido *pedido);
Cliente *clienteDaFrente(FilaEnc *fila);

#endif /* FILA_HPP */
