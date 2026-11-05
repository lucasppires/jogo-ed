#include <new>
#include "fila.hpp"

void inicializa(FilaEnc *f) 
{
    f->frente = nullptr;
    f->final  = nullptr;
}

bool estaVazia(FilaEnc *f) 
{
    return f->frente == nullptr;
}

bool enfileira(FilaEnc *f, Cliente valor) 
{
    Nodo *novo = new (std::nothrow) Nodo;
    if (novo == nullptr)
        return false;

    novo->dado = valor;
    novo->prox = nullptr;

    if (f->final != nullptr)
        f->final->prox = novo; // o antigo final passa a apontar para o novo nodo
    else
        f->frente = novo;      // fila estava vazia: novo nodo também é a frente

    f->final = novo;
    return true;
}

bool desenfileira(FilaEnc *f, Cliente *valorRemovido) 
{
    Nodo *removido;

    if (estaVazia(f)) // underflow
        return false;

    removido = f->frente;
    *valorRemovido = removido->dado;
    f->frente = removido->prox;

    if (f->frente == nullptr) // a fila ficou vazia
        f->final = nullptr;

    delete removido;
    return true;
}

int tamanho(FilaEnc *f) 
{
    Nodo *aux = f->frente;
    int contador = 0;

    while (aux != nullptr) {
        contador++;
        aux = aux->prox;
    }

    return contador;
}

void destruir(FilaEnc *fila)
{
    Cliente temp;
    while (!estaVazia(fila)) 
    {
        desenfileira(fila, &temp);
    }
}

bool criarClientes( FilaEnc *fila, int quantidade, int pacienciaInicial)
{
    for (int i = 0; i < quantidade; ++i) 
    {
        Cliente cliente;
        cliente.id = i + 1; // ids começam em 1
        cliente.paciencia_restante = pacienciaInicial;

        if (!enfileira(fila, cliente)) 
        {
            return false; // falha ao enfileirar
        }
    }
    return true;
}

Cliente *clienteDaFrente(FilaEnc *fila) 
{
    if (estaVazia(fila))
        return nullptr;

    return &fila->frente->dado;
}