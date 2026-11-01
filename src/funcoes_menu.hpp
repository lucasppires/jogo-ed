#ifndef FUNCOES_MENU_HPP
#define FUNCOES_MENU_HPP


#include "lista.hpp"


typedef enum {
    MENU = 0,
    NOVO_JOGO = 1,
    COMO_JOGAR = 2,
    HISTORICO = 3,
    SAIR = 4
} EstadoMenu;

void imprime_linha(int n);

void pula_linha(int n);

void imprimir_menu(int& estado_menu);

void como_jogar(int& estado_menu);

void historico(int& estado_menu, ListaContEst *lista_historico);

void historicov2(int& estado_menu, ListaContEst *lista_historico);

void historicov3(int& estado_menu, ListaContEst *lista_historico);

#endif
