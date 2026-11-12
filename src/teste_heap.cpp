#include <iostream>
#include "heap.hpp"
#include "ingredientes.hpp"
#include "teste_pilha.hpp"

using namespace std;

// farei uma min heap organizada em funcao do turno de vencimento!

// compilar g++ src/teste_heap.cpp src/heap.cpp src/ingredientes.cpp -o src/teste_heap.exe -Wall -std=c++17
// executar src/teste_heap.exe

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
bool prepararIngredienteNaoPerecivel(int quantidadesPereciveisDisponiveis[]){
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
                quantidadesPereciveisDisponiveis[0]++;
            break;
            
            case 'q':
                quantidadesPereciveisDisponiveis[1]++;
            break;

            case 'c':
                quantidadesPereciveisDisponiveis[2]++;
            break;

            case 't':
                quantidadesPereciveisDisponiveis[3]++;
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
        cout << "Alimento com o turno de vencimento " << vencimento << " foi removido" << endl;
    }
    return true;
}


// funcoes de usar ingredientes
// posteriormente serao interligadas com as funcoes da pilha, que adiciona os ingredientes preparados no hamburguer.

bool usaIngredientePerecivel(char codigo, FilaPrioridade *carnes, FilaPrioridade *ovos, FilaPrioridade *bacons, PilhaEnc *p){

    const Ingrediente *usado = buscarIngrediente(codigo);

    // digitou uma letra invalida
    if(usado == nullptr) return false;

    if (usado->perecivel == true){
        // se o campo perecivel do ingrediente é true, entao devemos armazenar esse ingrediente numa heap. Temos três ingreidentes pereciveis: carne, ovo frito e bacon.

        switch(usado->simbolo){
            case 'n':
                // para usar, deve existir pelo menos um ingrediente. Se existir, removemos-o da heap.
                if(fpEstaVazia(carnes)){
                    cout << "Nao ha carne disponivel!" << endl;
                    return false;
                }
                else{
                    int vencimento;

                    // so tira a unidade do heap se ela realmente entrou no hamburguer
                    bool resultado = adicionar_ingrediente(p, usado->simbolo);
                    if (!resultado){
                        cout << "Nao foi possivel adicionar carne." << endl;
                        return false;
                    }

                    fpRemoverMinimo(carnes, &vencimento);
                    cout << "Adicionaste carne." << endl;
                }
            break;

            case 'o':
                // para usar, deve existir pelo menos um ingrediente. Se existir, removemos-o da heap.
                if(fpEstaVazia(ovos)){
                    cout << "Nao ha ovo disponivel!" << endl;
                    return false;
                }
                else{
                    int vencimento;

                    bool resultado = adicionar_ingrediente(p, usado->simbolo);
                    if (!resultado){
                        cout << "Nao foi possivel adicionar ovo." << endl;
                        return false;
                    }

                    fpRemoverMinimo(ovos, &vencimento);
                    cout << "Adicionaste ovo." << endl;
                }

            break;

            case 'b':
                // para usar, deve existir pelo menos um ingrediente. Se existir, removemos-o da heap.
                if(fpEstaVazia(bacons)){
                    cout << "Nao ha bacon disponivel!" << endl;
                    return false;
                }
                else{
                    int vencimento;

                    bool resultado = adicionar_ingrediente(p, usado->simbolo);
                    if (!resultado){
                        cout << "Nao foi possivel adicionar bacon." << endl;
                        return false;
                    }

                    fpRemoverMinimo(bacons, &vencimento);
                    cout << "Adicionaste bacon." << endl;
                }
            break;
        }
        return true;
    }
    return false;
}

bool usaIngredienteNaoPerecivel(char codigo, int contadorDeQuantidadesDisponiveis[], PilhaEnc *p){

    const Ingrediente *usado = buscarIngrediente(codigo);

    // digitou uma letra invalida
    if(usado == nullptr) return false;


    // ADICIONA INGREDIENTE QUE NAO PRECISA DE ESTOQUE!
    // Pao de cima (z), Ketchup (k), Mostarda (m), Picles (p), Alface (a): quantidade infinita, vao direto pro hamburguer
    if(usado->perecivel == false and usado->requer_preparo == false){
        bool resultado = adicionar_ingrediente(p, usado->simbolo);
        if (!resultado){
            cout << "Nao foi possivel adicionar o ingrediente: " << usado->nome << endl;
            return false;
        }
        cout << "Adicionaste o ingrediente: " << usado->nome << endl;
        return true;
    }

    if(usado->perecivel == false and usado->requer_preparo == true){
        /* 
        o vetor possui 4 posicoes:
            posicao 0: Queijo suíço (s)
            poiscao 1: Queijo cheddar (q)
            posicao 2: Cebola (c)
            posicao 3: Tomate (t)
        */
        switch (usado->simbolo){
            // so desconta do estoque se o ingrediente realmente entrou no hamburguer
            case 's':
                if(contadorDeQuantidadesDisponiveis[0] > 0){
                    bool resultado = adicionar_ingrediente(p, usado->simbolo);
                    if (!resultado){
                        cout << "Nao foi possivel adicionar queijo suico." << endl;
                        return false;
                    }
                    contadorDeQuantidadesDisponiveis[0]--;
                }
                else{
                    cout << "Nao ha queijo suico disponivel!" << endl;
                    return false;
                }
            break;
            
            case 'q':
                if(contadorDeQuantidadesDisponiveis[1] > 0){
                    bool resultado = adicionar_ingrediente(p, usado->simbolo);
                    if (!resultado){
                        cout << "Nao foi possivel adicionar queijo cheddar." << endl;
                        return false;
                    }
                    contadorDeQuantidadesDisponiveis[1]--;
                }
                else{
                    cout << "Nao ha queijo cheddar disponivel!" << endl;
                    return false;
                }
            break;

            case 'c':
                if(contadorDeQuantidadesDisponiveis[2] > 0){
                    bool resultado = adicionar_ingrediente(p, usado->simbolo);
                    if (!resultado){
                        cout << "Nao foi possivel adicionar cebola." << endl;
                        return false;
                    }
                    contadorDeQuantidadesDisponiveis[2]--;
                }
                else{
                    cout << "Nao ha cebola disponivel!" << endl;
                    return false;
                }
            break;

            case 't':
                if(contadorDeQuantidadesDisponiveis[3] > 0){
                    bool resultado = adicionar_ingrediente(p, usado->simbolo);
                    if (!resultado){
                        cout << "Nao foi possivel adicionar tomate." << endl;
                        return false;
                    }
                    contadorDeQuantidadesDisponiveis[3]--;
                }
                else{
                    cout << "Nao ha tomate disponivel!" << endl;
                    return false;
                }
            break;
        }

        return true;
    }

    return false;

}

// Isso aqui deve ficar no inicio de cada turno do jogo!!
//removeIngredienteEstragado(turnoAtual, &carnes);
//removeIngredienteEstragado(turnoAtual, &ovos);
//removeIngredienteEstragado(turnoAtual, &bacons);



