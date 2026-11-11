#ifndef TESTE_PILHA_HPP
#define TESTE_PILHA_HPP

#include "pilha.hpp"
#include "pedido.hpp"
#include "ingredientes.hpp"
#include <iostream>

bool adicionar_ingrediente(PilhaEnc *p, char adicionado);
bool remover_ingrediente(PilhaEnc *p);
bool corrige_pedido(PilhaEnc *p, const ListaEnc *receita);
void imprimir_hamburguer(PilhaEnc *p);

#endif /* TESTE_PILHA_HPP */
