#ifndef FILA_HPP
#define FILA_HPP

struct Produto {
    int   cod;
    char  nome[50];
    float preco;
};

struct Nodo {
    Nodo   *prox;
    Produto dado;
};

struct FilaEnc {
    Nodo *frente;
    Nodo *final;
};

void inicializa(FilaEnc *f);
bool estaVazia(FilaEnc *f);
bool enfileira(FilaEnc *f, Produto valor);
bool desenfileira(FilaEnc *f, Produto *valorRemovido);
int  tamanho(FilaEnc *f);

#endif /* FILA_HPP */
