#include "pilha.hpp"
#include "pedido.hpp"
#include "ingredientes.hpp"
#include <iostream>

// comando de compilação:
// g++ teste_pilha.cpp pilha.cpp ingredientes.cpp listaenc.cpp -o teste_pilha -Wall -std=c++17
// .\teste_pilha.exe


using namespace std;

void adicionar_ingrediente(PilhaEnc *p){
    char adicionado;
    Ingrediente aux;


    cout << "Qual ingrediente tu quer adicionar? Informe a letra do ingrediente:";
    cin >> adicionado;

    aux.simbolo = adicionado;

    /*
    // Sem preparo e com quantidade infinita
inline const Ingrediente PAO{
    "Pao de cima", 'z', false, false, 0
};

inline const Ingrediente KETCHUP{
    "Ketchup", 'k', false, false, 0
};

inline const Ingrediente MOSTARDA{
    "Mostarda", 'm', false, false, 0
};

inline const Ingrediente PICLES{
    "Picles", 'p', false, false, 0
};

inline const Ingrediente ALFACE{
    "Alface", 'a', false, false, 0
};

// Com preparo, mas nao pereciveis
inline const Ingrediente QUEIJO_SUICO{
    "Queijo suico", 's', false, true, 0
};

inline const Ingrediente QUEIJO_CHEDDAR{
    "Queijo cheddar", 'q', false, true, 0
};

inline const Ingrediente CEBOLA{
    "Cebola", 'c', false, true, 0
};

inline const Ingrediente TOMATE{
    "Tomate", 't', false, true, 0
};

// Com preparo e pereciveis
inline const Ingrediente CARNE{
    "Carne", 'n', true, true, 3
};

inline const Ingrediente OVO_FRITO{
    "Ovo frito", 'o', true, true, 2
};

inline const Ingrediente BACON{
    "Bacon", 'b', true, true, 3
};

*/
    switch(aux.simbolo){
        case 'z':
        aux = PAO;
        break;

        case 'k':
        aux = KETCHUP;
        break;

        case 'm':
        aux = MOSTARDA;
        break;

        case 'p':
        aux = PICLES;
        break;

        case 'a':
        aux = ALFACE;
        break;

        case 's':
        aux = QUEIJO_SUICO;
        break;

        case 'q':
        aux = QUEIJO_CHEDDAR;
        break;

        case 'c':
        aux = CEBOLA;
        break;

        case 't':
        aux = TOMATE;
        break;

        case 'n':
        aux = CARNE;
        break;

        case 'o':
        aux = OVO_FRITO;
        break;

        case 'b':
        aux = BACON;
        break;

        default:
        {
        cout << "Tu passou um caractere invalido.\n";
        return;
        }
        break;

    }

    // verifica se o topo da pilha é o ingrediente PAO, se sim, nao pode adicionar mais ingredientes
    // tambem verifico se a pilha esta vazia; se sim, entao nao posso acessar a regiao da memoria do topo, q ainda nao foi alocada
    if (!estaVazia(p) && p->topo->dado.simbolo == PAO.simbolo) {
        cout << "Tu nao pode adicionar mais ingredientes, pois o hamburguer ja tem o pao de cima.\n";
        return;
    }

    // se eh perecivel, entao ele sai do heap. se o heap estiver vazio, nao pode realizar a acao.
    // heap ainda nao foi feito

    bool resultadoAdicao = empilha(p, aux);

    if (resultadoAdicao) 
        cout << "Empilhaste o ingrediente: " << aux.nome << endl;

    return;
}

void remover_ingrediente(PilhaEnc *p){
    Ingrediente aux;

    bool resultadoRemocao = desempilha(p, &aux);

    
    if (resultadoRemocao) 
        cout << "Desempilhaste o ingrediente: " << aux.nome << endl;
    else
        cout << "Nao foi possivel remover o ingrediente. O hamburguer esta vazio." << endl;

    return;
}


bool corrige_pedido(PilhaEnc *p, ListaEnc *receita){
    // primeiro vamos colocar os ingredientes da pilha em uma vetor de ingredientes, para depois comparar com a receita, que é uma lista enc.


    Ingrediente vetorCorrecao[tamanho(p)];   // o tamanho do vetor é o tamanho da pilha
    int n = tamanho(p);
    int i = tamanho(p) - 1;

    // vê se ambas as estruturas - array e lista - tem o mesmo tamanho, se nn tiver, deu merda no pedido

    if (n != tamanho(receita)) {
        cout << "Montaste o pedido com a quantidade errada de ingredientes!" << endl;
        return false;
    }



    while (!estaVazia(p)) {
        Ingrediente aux;
        desempilha(p, &aux);

        vetorCorrecao[i] = aux;
        i--;
    }

    i = 0;

    NodoReceita *aux = receita->ini;

    while(aux != nullptr){
        if(aux->dado.simbolo != vetorCorrecao[i].simbolo){
            cout << "Seu idiota, montaste o pedido na ordem errada!" << endl;
            return false;
        }

        aux = aux->prox;
        i++;
    }
    return true;
}

void imprimir_hamburguer(PilhaEnc *p){
    Nodo* aux = p->topo;

    if (aux == nullptr) {
        cout << "Teu hamburguer esta vazio" << endl;
        return;
    }

    cout << "Teu hamburguer tem os seguintes ingredientes: " << endl;

    // sim, pode acessar a esturtura interna da pilha, a especificacao nao proibe.
    while (aux != nullptr) {
        cout << aux->dado.cor << aux->dado.nome << cores::RESET << endl;
        aux = aux->prox;
    }

    cout << "Pao de baixo" << endl;
    return;
}



// ia gerou um main pra eu testar
int main(){
    PilhaEnc p;
    inicializa(&p);

    // receita de exemplo, da base para o topo: bacon, carne, cheddar, pao
    ListaEnc receita;
    inicializar(&receita);
    const char *simbolosReceita = "bnqz";
    for (int i = 0; simbolosReceita[i] != '\0'; i++)
        inserirFim(&receita, *buscarIngrediente(simbolosReceita[i]));

    cout << "\n--- 1. pilha vazia ---\n";
    imprimir_hamburguer(&p);
    remover_ingrediente(&p);

    cout << "\n--- 2. pilha de exemplo ---\n";
    montarPilhaViaSimbolos(&p, "bnq");
    imprimir_hamburguer(&p);

    cout << "\n--- 3. adicionar: digite a (alface) ---\n";
    adicionar_ingrediente(&p);
    imprimir_hamburguer(&p);

    cout << "\n--- 4. remover (sai a alface) ---\n";
    remover_ingrediente(&p);
    imprimir_hamburguer(&p);

    cout << "\n--- 5. adicionar: digite z (pao de cima) ---\n";
    adicionar_ingrediente(&p);

    cout << "\n--- 6. adicionar: digite t (deve bloquear) ---\n";
    adicionar_ingrediente(&p);

    cout << "\n--- 7. adicionar: digite x (invalido) ---\n";
    adicionar_ingrediente(&p);
    imprimir_hamburguer(&p);

    cout << "\n--- 8. corrigir: pedido certo (esperado 1) ---\n";
    cout << corrige_pedido(&p, &receita) << endl;

    cout << "\n--- 9. corrigir: ordem errada (esperado 0) ---\n";
    montarPilhaViaSimbolos(&p, "nbqz");
    cout << corrige_pedido(&p, &receita) << endl;

    cout << "\n--- 10. corrigir: quantidade errada (esperado 0) ---\n";
    montarPilhaViaSimbolos(&p, "bn");
    cout << corrige_pedido(&p, &receita) << endl;

    esvaziarPilha(&p);
    destruir(&receita);
    return 0;
}