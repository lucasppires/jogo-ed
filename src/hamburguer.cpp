#include "pilha.hpp"
#include "pedido.hpp"
#include "ingredientes.hpp"
#include <iostream>
#include <new>

// comando de compilação:
// g++ -DTESTE_PILHA_MAIN hamburguer.cpp pilha.cpp ingredientes.cpp listaenc.cpp -o teste_pilha -Wall -std=c++17
// .\teste_pilha.exe


using namespace std;

bool adicionar_ingrediente(PilhaEnc *p, char adicionado){
    Ingrediente aux;


   // cout << "Qual ingrediente tu quer adicionar? Informe a letra do ingrediente:";
 //   cin >> adicionado;

    aux.simbolo = adicionado;

    /*
    // sem preparo e com quantidade infinita
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

// com preparo, mas nao pereciveis
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

// com preparo e pereciveis
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

        // o controle de estoque (heap) eh feito em usaIngredientePerecivel (preparo.cpp)
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
        return false;
        }
        break;

    }

    // verifica se o topo da pilha é o ingrediente PAO, se sim, nao pode adicionar mais ingredientes
    // o !estaVazia(p) é para evitar que o programa tente acessar p->topo->dado.simbolo quando a pilha estiver vazia, o que causaria um erro de segmentação
    if (!estaVazia(p) && p->topo->dado.simbolo == PAO.simbolo) {
        cout << "Tu nao pode adicionar mais ingredientes, pois o hamburguer ja tem o pao de cima.\n";
        return false;
    }

    // se eh perecivel, entao ele sai do heap. se o heap estiver vazio, nao pode realizar a acao
    // heap ainda nao foi feito

    bool resultadoAdicao = empilha(p, aux);

    if (resultadoAdicao) {
        cout << "Empilhaste o ingrediente: " << aux.nome << endl;
        return true;
    } else {
        cout << "Nao foi possivel adicionar o ingrediente. O hamburguer ja tem o pao de cima ou o ingrediente nao esta disponivel." << endl;
        return false;
}
}

bool remover_ingrediente(PilhaEnc *p){
    Ingrediente aux;

    bool resultadoRemocao = desempilha(p, &aux);

    
    if (resultadoRemocao) {
        cout << "Desempilhaste o ingrediente: " << aux.nome << endl;
        return true;
    }
    else {
        cout << VERMELHO << "Nao podes remover o pao de baixo." << cores::RESET << endl;
        return false;
    }
}


bool corrige_pedido(PilhaEnc *p, const ListaEnc *receita)
{
    int n = tamanho(p);
    if (n != tamanho(receita)) {
        return false;
    }

    if (n == 0) {
        return true;
    }

    char *simbolos = new (nothrow) char[n];
    if (simbolos == nullptr) {
        cerr << "Nao foi possivel conferir o pedido.\n";
        return false;
    }

    // le do topo pra base e guarda ao contrario, sem retirar nenhum no da pilha
    int i = n - 1;
    for (const NodoPilha *atual = p->topo; atual != nullptr; atual = atual->prox) {
        simbolos[i] = atual->dado.simbolo;
        i--;
    }

    bool correto = true;
    i = 0;
    for (const NodoReceita *atual = receita->ini; atual != nullptr; atual = atual->prox) {
        if (atual->dado.simbolo != simbolos[i]) {
            cout << "A ordem dos ingredientes nao corresponde a receita.\n";
            correto = false;
            break;
        }
        i++;
    }

    // o vetor e temporario; o hamburguer continua montado para o jogador corrigir
    delete[] simbolos;
    return correto;
}

void imprimir_hamburguer(PilhaEnc *p){
    NodoPilha* aux = p->topo;


    cout << "Teu hamburguer tem os seguintes ingredientes:\n " << endl;

    if (aux == nullptr) 
    {
        cout << LARANJA << "Pao de baixo" << cores:: RESET << endl;
        return;
    }

    else {

        // sim, pode acessar a esturtura interna da pilha, a especificacao nao proibe
        while (aux != nullptr) {
            cout << aux->dado.cor << aux->dado.nome << cores::RESET << endl;
            aux = aux->prox;
        }

        cout << LARANJA << "Pao de baixo" << cores:: RESET << endl;
        return;
    }

    cout << "\n";
}



// escolhe o desenho de cada ingrediente pelo seu simbolo
static const char *desenho_ingrediente(char simbolo)
{
    switch (simbolo) {
        case 'k': return " ~~~ ~~~ ~~~ ~~~ ~~~ ";
        case 'm': return " --- --- --- --- --- ";
        case 'p': return "  (o)  (o)  (o)  (o) ";
        case 'a': return R"( /\/\/\/\/\/\/\/\/\/\ )";
        case 's': return " [o---o---o---o---o] ";
        case 'q': return " [=================] ";
        case 'c': return "  ()  ()  ()  ()  () ";
        case 't': return " (:::)(:::)(:::)(:::) ";
        case 'n': return " [#################] ";
        case 'o': return " (_______(o)_______) ";
        case 'b': return " ~~=====~~=====~~=== ";
        default:  return " [-----------------] ";
    }
}

void desenhar_hamburguer(const PilhaEnc *p)
{
    cout << "\nHAMBURGUER\n\n";

    // percorre do topo pra base sem desempilhar os ingredientes
    for (const NodoPilha *atual = p->topo; atual != nullptr; atual = atual->prox) 
    {
        const Ingrediente &ingrediente = atual->dado;

        // o pao de cima ocupa mais de uma linha pra formar a tampa
        if (ingrediente.simbolo == PAO.simbolo) 
        {
            cout << ingrediente.cor
                  << "      .--------.\n"
                 << "   .-'   . . .  '-.\n"
                 << "  /________________\\";
        } 
        else 
        {
            cout << ingrediente.cor << desenho_ingrediente(ingrediente.simbolo);
        }

        // imprime o nome na mesma cor do desenho e so depois reseta a cor
        cout << "  " << ingrediente.nome << cores::RESET << '\n';
    }

    // o pao de baixo nao fica na pilha e aparece mesmo quando ela esta vazia
    cout << cores::LARANJA
         << " \\_________________/  Pao de baixo" << cores::RESET << '\n'
         << cores::LARANJA << "  '---------------'" << cores::RESET << '\n';
}

// ia gerou um main pra eu testar
// so eh compilado com -DTESTE_PILHA_MAIN (senao conflita com o main.cpp do jogo)
#ifdef TESTE_PILHA_MAIN
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
    adicionar_ingrediente(&p, 'a');
    imprimir_hamburguer(&p);

    cout << "\n--- 4. remover (sai a alface) ---\n";
    remover_ingrediente(&p);
    imprimir_hamburguer(&p);

    cout << "\n--- 5. adicionar: digite z (pao de cima) ---\n";
    adicionar_ingrediente(&p, 'z');

    cout << "\n--- 6. adicionar: digite t (deve bloquear) ---\n";
    adicionar_ingrediente(&p, 't');

    cout << "\n--- 7. adicionar: digite x (invalido) ---\n";
    adicionar_ingrediente(&p, 'x');
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
#endif // teste_PILHA_MAIN
