#include "heap.hpp"
#include "ingredientes.hpp"
#include <iostream>
using namespace std;

// farei uma min heap organizada em funcao do turno de vencimento!

int calculaTurnoVencimento(int turnoAtual, const Ingrediente *ing){
    return turnoAtual + ing->validade_turnos;
}


// prepara os ingredintes que PRECISAM DE ESTOQUE. Pão de cima (z), Ketchup (k), Mostarda (m), Picles (p), Alface (a) nao precisam de estoque.
// true == conseguiu preparar e armazenar na min heap.
bool prepararIngredientePerecivel(int turnoAtual, FilaPrioridade *carnes, FilaPrioridade *ovos, FilaPrioridade *bacons){
    char codigo;
    cout << "Informe o codigo do ingrediente que queres preparar:" << endl;
    cin >> codigo;

    const Ingrediente *preparado = buscarIngrediente(codigo);

    // digitou uma letra invalida
    if(preparado == nullptr) return false;

    if (preparado->perecivel == true){
        // se o campo perecivel do ingrediente é true, entao devemos armazenar esse ingrediente numa heap. Temos três ingreidentes pereciveis: carne, ovo frito e bacon.

        switch(preparado->simbolo){
            case 'n':
                {
                bool resultadoInsercaoHeap = fpInserir(carnes, calculaTurnoVencimento(turnoAtual, preparado));
                if(!resultadoInsercaoHeap){
                    cout << "Deu merda" << endl;
                    return false;
                    }
                }
            break;

            case 'o':
                {
                bool resultadoInsercaoHeap = fpInserir(ovos, calculaTurnoVencimento(turnoAtual, preparado));
                if(!resultadoInsercaoHeap){
                    cout << "Deu merda" << endl;
                    return false;
                    }
                }
            break;

            case 'b':
                {
                bool resultadoInsercaoHeap = fpInserir(bacons, calculaTurnoVencimento(turnoAtual, preparado));
                if(!resultadoInsercaoHeap){
                    cout << "Deu merda" << endl;
                    return false;
                    }
                }
            break;

            default:
                return false;
            break;
        }
        return true;
    }
    return false;
}

// são eles: Queijo suíço (s), Queijo cheddar (q), Cebola (c), Tomate (t)
bool prepararIngredientePerene(int contadorDeQuantidadesDisponiveis[]){
    char codigo;
    cout << "Informe o codigo do ingrediente que queres preparar:" << endl;
    cin >> codigo;

    const Ingrediente *preparado = buscarIngrediente(codigo);

    // digitou uma letra invalida
    if(preparado == nullptr) return false;

    if(preparado->perecivel == false and preparado->requer_preparo == true){
        /* 
        o vetor possui 4 posicoes:
            posicao 0: Queijo suíço (s)
            poiscao 1: Queijo cheddar (q)
            posicao 2: Cebola (c)
            posicao 3: Tomate (t)
        */
        switch (preparado->simbolo){
            case 's':
                contadorDeQuantidadesDisponiveis[0]++;
            break;
            
            case 'q':
                contadorDeQuantidadesDisponiveis[1]++;
            break;

            case 'c':
                contadorDeQuantidadesDisponiveis[2]++;
            break;

            case 't':
                contadorDeQuantidadesDisponiveis[3]++;
            break;
        }

        return true;
    }

    return false;

}

// remove ingrediente cuja validade ja passou
bool removeIngredienteEstragado(int turnoAtual, FilaPrioridade* turnosDeVencimento){
    // se o turno de vencimento for <= turno atual, então a unidade é removida
    int vencimento; // variavel que vai receber o valor do turno de vencimento atual

    while(fpMinimo(turnosDeVencimento, &vencimento) and (vencimento <= turnoAtual)){
        fpRemoverMinimo(turnosDeVencimento, &vencimento);
    }
}


bool usaIngredientePerecivel(int turnoAtual, FilaPrioridade *carnes, FilaPrioridade *ovos, FilaPrioridade *bacons){
    char codigo;
    cout << "Informe o codigo do ingrediente que queres usar:" << endl;
    cin >> codigo;

    const Ingrediente *usado = buscarIngrediente(codigo);

    // digitou uma letra invalida
    if(preparado == nullptr) return false;

    if (preparado->perecivel == true){
        // se o campo perecivel do ingrediente é true, entao devemos armazenar esse ingrediente numa heap. Temos três ingreidentes pereciveis: carne, ovo frito e bacon.

        switch(preparado->simbolo){
            case 'n':

            break;

            case 'o':

            break;

            case 'b':

            break;
        }
    }
}









int main(){




}