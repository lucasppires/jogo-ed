#include "pilha.hpp"
#include "pedido.hpp"
#include "ingredientes.hpp"
#include <iostream>

using namespace std;

void adicionar_ingrediente(){
    PilhaEnc p;
    inicializa(&p);
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

    // se eh perecivel, entao ele sai do heap. se o heap estiver vazio, nao pode realizar a acao.
    // heap ainda nao foi feito

    bool resultadoAdicao = empilha(&p, aux);

    if (resultadoAdicao) 
        cout << "Empilhaste o ingrediente: " << aux.nome << endl;

    return;
}



int main(){
    adicionar_ingrediente();
    return 0;
}
