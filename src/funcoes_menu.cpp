#include <iostream>
#include <fstream>
#include <string>
#include "funcoes_menu.hpp"
#include "cores.hpp"
using std::cout;
using std::cin;
using std::scanf;
using std::endl;

void imprime_linha(int n)
{
    for (int i = 0; i < n; i++)
        std::printf("#");
}

void pula_linha(int n)
{
    for (int i = 0; i < n; i++)
        std::printf("\n");
}

void imprimir_menu(int& estado_menu)
{
    imprime_linha(44);
            pula_linha(1);
            cout << cores::AZUL <<"\t\tDADO BURGER\n";
            pula_linha(1);
            cout << cores::AMARELO <<"\t\t1. Novo jogo\n";
            cout << cores::VERMELHO <<"\t\t2. Como jogar\n";
            cout << cores::VERDE <<"\t\t3. Historico\n";
            cout << cores::MAGENTA <<"\t\t4. Sair\n" << cores::RESET;
        
            pula_linha(1);
            imprime_linha(44);
            pula_linha(2);

            cout << "Digite a opcao desejada: ";

            cin >> estado_menu;
}

void como_jogar(int& estado_menu)
{
    cout << R"(
COMO JOGAR - DADO BURGER

Voce e o novo funcionario do Dado Burger! Atenda todos os clientes antes que a paciencia deles acabe.

MONTANDO O PEDIDO
Confira a receita do cliente e adicione os ingredientes na ordem indicada, de baixo para cima. O pao de baixo ja esta no prato. Finalize com o pao de cima: o hamburguer precisa corresponder exatamente a receita.

Voce so pode remover o ingrediente do topo. Ingredientes removidos sao descartados e nao voltam ao estoque. Nao e possivel adicionar ingredientes acima do pao de cima.

INGREDIENTES
Sem preparo e com quantidade infinita:
z - Pao de cima
k - Ketchup
m - Mostarda
p - Picles
a - Alface

Precisam de preparo e nao vencem no estoque:
s - Queijo suico
q - Queijo cheddar
c - Cebola
t - Tomate

Precisam de preparo e vencem no estoque:
n - Carne
o - Ovo frito
b - Bacon

ACOES E TURNOS
Preparar uma unidade de ingrediente: 1 turno.
Adicionar um ingrediente ao hamburguer: 1 turno.
Remover o ingrediente do topo: 1 turno.
Consultar o pedido ou o estoque: nao gasta turno.

ESTOQUE E VALIDADE
Prepare os ingredientes antes de usa-los. Carne, ovo e bacon vencidos sao descartados automaticamente no inicio de cada turno. Ao usar um perecivel, sai primeiro a unidade mais proxima do vencimento.

VITORIA E DERROTA
Somente o cliente em atendimento perde paciencia a cada acao que gasta turno. Se ela chegar a zero antes de concluir o pedido, a partida termina.

Atenda todos os clientes para vencer!
Sua pontuacao e o numero de clientes atendidos.


Selecione uma opcao:

1. Jogar
2. Voltar ao menu
)";

    int opcao;
    cin >> opcao;

    if (opcao == 1)
    {
        estado_menu = NOVO_JOGO;
    }
    else if (opcao == 2)
    {
        estado_menu = MENU;
    }
}