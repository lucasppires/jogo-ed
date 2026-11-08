#include <new>
#include "pilha.hpp"
#include "ingredientes.hpp"

void inicializa(PilhaEnc *p) {
    p->topo = nullptr;
}

bool estaVazia(PilhaEnc *p) {
    return p->topo == nullptr;
}

bool empilha(PilhaEnc *p, Ingrediente adicionado) {
    Nodo *novo = new (std::nothrow) Nodo;
    if (novo == nullptr)
        return false;

    novo->dado = adicionado;
    novo->prox = p->topo; // aponta para o antigo topo
    p->topo = novo;       // o novo nodo passa a ser o topo
    return true;
}

bool desempilha(PilhaEnc *p, Ingrediente *removido) {
    Nodo *aux;

    if (estaVazia(p)) // underflow
        return false;

    *removido = p->topo->dado;
    aux = p->topo;
    p->topo = p->topo->prox;
    delete aux;
    return true;
}

bool topo(PilhaEnc *p, Ingrediente *valor) {
    if (estaVazia(p))
        return false;

    *valor = p->topo->dado;
    return true;
}

int tamanho(PilhaEnc *p) {
    Nodo *aux = p->topo;
    int contador = 0;

    while (aux != nullptr) {
        contador++;
        aux = aux->prox;
    }

    return contador;
}

void esvaziarPilha(PilhaEnc *p){
    Ingrediente lixo;
    while (desempilha(p, &lixo)) {}
}

void montarPilhaViaSimbolos(PilhaEnc *p, const char *simbolos){
    esvaziarPilha(p);
    for (int i = 0; simbolos[i] != '\0'; i++)
        empilha(p, *buscarIngrediente(simbolos[i]));
}