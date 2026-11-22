#include <iostream>
#include "heap.hpp"
#include "ingredientes.hpp"
#include "hamburguer.hpp"

using namespace std;

// farei uma min heap organizada em funcao do turno de vencimento!

// compilar g++ src/preparo.cpp src/heap.cpp src/ingredientes.cpp -o src/teste_heap.exe -Wall -std=c++17
// executar src/teste_heap.exe




// simples, a cada cliente que esta aguardando seu pedido é calculado um turno, é a partir desse turno que é calculado o vencimento do ingrediente.
// se um ingrediente foi produzido no turno 2 e tem validade 3, ele vence no inicio do turno 6,
// e pode ser usado em tres turnos - no caso o 3, 4 e 5.
int calculaTurnoVencimento(int turnoAtual, const Ingrediente *ing){
    return turnoAtual + ing->validade_turnos + 1;
}


// prepara os ingredintes que PRECISAM DE ESTOQUE. Pão de cima (z), Ketchup (k), Mostarda (m), Picles (p), Alface (a) nao precisam de estoque
// true == conseguiu preparar e armazenar na min heap

// repare que eu passo por referencia todas as min-heaps, isso pq nao sei em qual o usuario pode inserir.
bool prepararIngredientePerecivel(int turnoAtual, FilaPrioridade *carnes, FilaPrioridade *ovos, FilaPrioridade *bacons){
    char codigo;
    cout << "Informe o codigo do ingrediente que queres preparar:" << endl;
    cin >> codigo;

    const Ingrediente *preparado = buscarIngrediente(codigo);

    // digitou uma letra invalida,
    if(preparado == nullptr) 
    {
        cout << "Ingrediente invalido.\n";
        return false;
    }

    if (preparado->perecivel == true){
        // se o campo perecivel do ingrediente é true, entao devemos armazenar esse ingrediente numa heap. Temos três ingreidentes pereciveis: carne, ovo frito e bacon

        switch(preparado->simbolo){
            case 'n':
                {
                    // a funcao fpInserir insere na min-heap um inteiro
                    // no caso, aqui ela esta inserindo na min-heap CARNES o turno de vencimento dessa carne que recem foi preparada
                    // isso faz sentido pq a nossa chave de prioridade, como explicitado no relatorio, é o turno de vencimento do ingrediente adicionado.
                bool resultadoInsercaoHeap = fpInserir(carnes, calculaTurnoVencimento(turnoAtual, preparado));
                if(!resultadoInsercaoHeap){
                    cout << "Deu merda" << endl;
                    return false;
                    }
                }
            break;

            case 'o':
                {
                    // o mesmo vale pras outras min-heaps
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

// funcao importante, passo a ela um array, cada posicao do array representa uma quantidade de um dos 4 ingredientes n perecivieis q necessitam estoque
bool prepararIngredienteNaoPerecivel(int quantidadesPereciveisDisponiveis[]){
    char codigo;
    cout << "Informe o codigo do ingrediente que queres preparar:" << endl;
    cin >> codigo;

    const Ingrediente *preparado = buscarIngrediente(codigo);

    // digitou uma letra invalida
    if(preparado == nullptr)
    {
        cout << "Ingrediente invalido.\n";
        return false;
    }

    if(preparado->perecivel == false and preparado->requer_preparo == true){
        /* 
        o vetor possui 4 posicoes:
            posicao 0: Queijo suíço (s)
            poiscao 1: Queijo cheddar (q)
            posicao 2: Cebola (c)
            posicao 3: Tomate (t)
        */

        // intuitivo, aumenta o valor daquele ingrediente se voce preparou ele
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
// a essa funcao é passado o turno atual, ele é crucial no calculo
// e é passada uma fila de prioridade qualquer. isso porque, no jogo em si, aplico essa funcao às tres min-heaps a cada turno que passa,
// com o objetivo de sempre veriifcar se algo estragou

bool removeIngredienteEstragado(int turnoAtual, FilaPrioridade* turnosDeVencimento){
    // se o turno de vencimento for <= turno atual, então a unidade é removida

    int vencimento; // variavel que vai receber o valor do turno de vencimento atual

    while(fpMinimo(turnosDeVencimento, &vencimento) and (vencimento <= turnoAtual)){
            // vamos por partes
            // fpMinimo retorna o menor valor do min-heap.
            // esse valor é salvo na variavel vencimento
            // essa funcao fpMinimo so vai retornar false se a min-heap estiver vazia

            // esse valor salvo em vencimento deve ser menor que o turno atual pra esse ingrediente nao ser vencido.

            // é um while mas tipo, como essa funcao acontece a cada turno, ela sempre vai remover no maximo um ingrediente por turno.

        fpRemoverMinimo(turnosDeVencimento, &vencimento); // aqui ocorre a remocao de fato, o valor é salvo na variavel vencimento

        cout << "Alimento com o turno de vencimento " << vencimento << " foi removido" << endl;
    }
    return true;
}






// funcoes de usar ingredientes
// posteriormente serao interligadas com as funcoes da pilha, que adiciona os ingredientes preparados no hamburguer

bool usaIngredientePerecivel(char codigo, FilaPrioridade *carnes, FilaPrioridade *ovos, FilaPrioridade *bacons, PilhaEnc *p){

    // Primeiramente, é buscado qual ingrediente bate com o codigo que o usuario quer adicionar ao hamburguer.
    const Ingrediente *usado = buscarIngrediente(codigo);

    // digitou uma letra invalida
    if(usado == nullptr) return false;

    if (usado->perecivel == true){
        // se o campo perecivel do ingrediente é true, entao devemos armazenar esse ingrediente numa heap. Temos três ingreidentes pereciveis: carne, ovo frito e bacon

        switch(usado->simbolo){
            case 'n':
                // Intuitivo. para usar, deve existir pelo menos um ingrediente. Se existir, removemos-o da heap
                if(fpEstaVazia(carnes)){
                    cout << "Nao ha carne disponivel!" << endl;
                    return false;
                }
                else{
                    // Se a min-heap não está vazia, ...
                    int vencimento;

                    // so tira a unidade do heap se ela realmente entrou no hamburguer
                    bool resultado = adicionar_ingrediente(p, usado->simbolo);
                    if (!resultado){
                        cout << "Nao foi possivel adicionar carne." << endl;
                        return false;
                    }

                    // remove da heap. 
                    // ele remove aquele que tem maior prioridade, isto é, aquele que tem o menor turno de vencimento da min-heap.
                    fpRemoverMinimo(carnes, &vencimento);
                    cout << "Adicionaste carne." << endl;
                }
            break;

            // AS MESMAS EXPLICACOES VALEM PRO OVO E PRO BACON.

            case 'o':
                // para usar, deve existir pelo menos um ingrediente. Se existir, removemos-o da heap
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
                // para usar, deve existir pelo menos um ingrediente. Se existir, removemos-o da heap
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

// A essa funcao nao eh passado os min-heaps, obviamente,
// porque os naoPereciveis sao passados em array.
bool usaIngredienteNaoPerecivel(char codigo, int contadorDeQuantidadesDisponiveis[], PilhaEnc *p){

    // ve qual ingrediente bate com o do usuario
    const Ingrediente *usado = buscarIngrediente(codigo);

    // digitou uma letra invalida
    if(usado == nullptr) return false;


    // adiciona INGREDIENTE QUE NAO PRECISA DE ESTOQUE!
    // pao de cima (z), Ketchup (k), Mostarda (m), Picles (p), Alface (a): quantidade infinita, vao direto pro hamburguer
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

                // Primeiro verifica se naquela posicao a posicao é maior que zero
                // se a posicao eh zero, entao o estoque desse ingrediente ta vazio
                if(contadorDeQuantidadesDisponiveis[0] > 0){

                    // adiciona o ingrediente à pilha.
                    bool resultado = adicionar_ingrediente(p, usado->simbolo);
                    if (!resultado){
                        cout << "Nao foi possivel adicionar queijo suico." << endl;
                        return false;
                    }

                    // diminui a quantidade desse ingrediente em 1 unidade.
                    contadorDeQuantidadesDisponiveis[0]--;
                }
                else{
                    cout << "Nao ha queijo suico disponivel!" << endl;
                    return false;
                }

            break;
            

            // O MESMO VALE PRA TODOS!
            
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

// isso aqui deve ficar no inicio de cada turno do jogo!!
//removeIngredienteEstragado(turnoAtual, &carnes);
//removeIngredienteEstragado(turnoAtual, &ovos);
//removeIngredienteEstragado(turnoAtual, &bacons);



