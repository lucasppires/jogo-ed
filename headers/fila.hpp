#ifndef FILAENC_H
#define FILAENC_H

typedef struct {
    int cod;
    char nome[50];
    float preco;
} Produto;

typedef struct str_Nodo Nodo;

struct str_Nodo {
    Nodo *prox;
    Produto dado;
};

typedef struct {
    Nodo *frente;
    Nodo *final;
} FilaEnc;

void inicializa(FilaEnc *f);
int  estaVazia(FilaEnc *f);
int  enfileira(FilaEnc *f, Produto valor);
int  desenfileira(FilaEnc *f, Produto *valorRemovido);
int  tamanho(FilaEnc *f);

#endif
