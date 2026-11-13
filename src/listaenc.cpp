#include <iostream>
#include <new>
#include "listaenc.hpp"
#include <iostream>
#include <iomanip>
using namespace std;

namespace 
{
constexpr int larguraIngrediente = 22;
constexpr int larguraSimbolo = 10;
constexpr int larguraPerecivel = 12;
constexpr int larguraPreparo = 18;
}

static void imprimirIngrediente(const Ingrediente &ing)
{
    std::cout << std::setw(larguraIngrediente) << ing.nome
              << std::setw(larguraSimbolo) << ing.simbolo
              << std::setw(larguraPerecivel) << (ing.perecivel ? "Sim" : "Nao") //operador ternario, se ing.perecivel for true, imprime "Sim", senao imprime "Nao"
              << std::setw(larguraPreparo) << (ing.requer_preparo ? "Sim" : "Nao")
              << (ing.validade_turnos ? std::to_string(ing.validade_turnos) : "-") << '\n';
}



void inicializar(ListaEnc *lista) {
    lista->ini = nullptr;
}

int tamanho(const ListaEnc *lista) {
    const NodoReceita *aux = lista->ini;
    int contador = 0;

    while (aux != nullptr) {
        contador++;
        aux = aux->prox;
    }

    return contador;
}

void imprimir(const ListaEnc *lista)
{
    const NodoReceita *aux = lista->ini;
    const auto formatoAnterior = std::cout.flags();

    std::cout << "ADICIONE:\n\n"
              << std::left
              << std::setw(larguraIngrediente) << "Ingrediente"
              << std::setw(larguraSimbolo) << "Codigo"
              << std::setw(larguraPerecivel) << "Perecivel?"
              << std::setw(larguraPreparo) << "Requer preparo?"
              << "Validade (turnos)\n\n";

    while (aux != nullptr)
    {
        imprimirIngrediente(aux->dado);
        aux = aux->prox;
    }

    std::cout << '\n';
    std::cout.flags(formatoAnterior);
}
Ingrediente buscar(const ListaEnc *lista, char simbolo) {
    const NodoReceita *aux = lista->ini;

    while (aux != nullptr) {
        if (aux->dado.simbolo == simbolo)
            return aux->dado;

        aux = aux->prox;
    }

    // Simbolo nulo indica ingrediente nao encontrado.
    return Ingrediente{"", '\0', false, false, 0};
}

int inserirInicio(ListaEnc *lista, Ingrediente ing) {
    NodoReceita *novo = new (std::nothrow) NodoReceita;

    if (novo == nullptr)
        return 0;

    novo->dado = ing;
    novo->prox = lista->ini;
    lista->ini = novo;

    return 1;
}

int inserirFim(ListaEnc *lista, Ingrediente ing) {
    NodoReceita *novo = new (std::nothrow) NodoReceita;

    if (novo == nullptr)
        return 0;

    novo->dado = ing;
    novo->prox = nullptr;

    if (lista->ini == nullptr) {
        lista->ini = novo;
    } else {
        NodoReceita *aux = lista->ini;

        while (aux->prox != nullptr)
            aux = aux->prox;

        aux->prox = novo;
    }

    return 1;
}

int removerPorSimbolo(ListaEnc *lista, char simbolo) {
    NodoReceita *ant = nullptr;
    NodoReceita *aux = lista->ini;

    while (aux != nullptr && aux->dado.simbolo != simbolo) {
        ant = aux;
        aux = aux->prox;
    }

    if (aux == nullptr)
        return 0;

    if (ant == nullptr)
        lista->ini = aux->prox;
    else
        ant->prox = aux->prox;

    delete aux;
    return 1;
}

void destruir(ListaEnc *lista) {
    NodoReceita *aux = lista->ini;

    while (aux != nullptr) {
        NodoReceita *removido = aux;
        aux = aux->prox;
        delete removido;
    }

    lista->ini = nullptr;
}


