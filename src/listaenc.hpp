#ifndef LISTAENC_HPP
#define LISTAENC_HPP

#include "ingredientes.hpp"

struct NodoReceita {
    NodoReceita *prox;
    Ingrediente dado;
};

struct ListaEnc {
    NodoReceita *ini;
};

void inicializar(ListaEnc *lista);
int tamanho(const ListaEnc *lista);
void imprimir(const ListaEnc *lista);

Ingrediente buscar(const ListaEnc *lista, char simbolo);
const Ingrediente *buscarIngrediente(char simbolo);

int inserirInicio(ListaEnc *lista, Ingrediente ing);
int inserirFim(ListaEnc *lista, Ingrediente ing);
int removerPorSimbolo(ListaEnc *lista, char simbolo);


void destruir(ListaEnc *lista);

#endif