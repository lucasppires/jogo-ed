#ifndef TESTE_HEAP_HPP
#define TESTE_HEAP_HPP

#include "heap.hpp"
#include "ingredientes.hpp"
#include "teste_pilha.hpp"
#include <iostream>

int  calculaTurnoVencimento(int turnoAtual, const Ingrediente *ing);

bool prepararIngredientePerecivel(int turnoAtual, FilaPrioridade *carnes, FilaPrioridade *ovos, FilaPrioridade *bacons);
bool prepararIngredienteNaoPerecivel(int contadorDeQuantidadesDisponiveis[]);

bool removeIngredienteEstragado(int turnoAtual, FilaPrioridade *turnosDeVencimento);

bool usaIngredientePerecivel(char codigo, FilaPrioridade *carnes, FilaPrioridade *ovos, FilaPrioridade *bacons, PilhaEnc *p);
bool usaIngredienteNaoPerecivel(char codigo, int contadorDeQuantidadesDisponiveis[], PilhaEnc *p);

#endif /* TESTE_HEAP_HPP */
