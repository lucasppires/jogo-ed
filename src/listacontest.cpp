#include <iostream>
#include "listacontest.hpp"
#include "timer.hpp"

void inicializar(ListaContEst *l) {
    l->tamanho = 0;
    l->capacidade = CAPACIDADE;
    l->dados = new Jogador[l->capacidade];
}

int tamanho(const ListaContEst *l) {
    return l->tamanho;
}

bool inserir(ListaContEst *l, Jogador novo, int pos) {
    if (pos < 0 || pos > l->tamanho)
        return false;

    if (l->tamanho == l->capacidade) {
        int novaCapacidade = l->capacidade * 2;
        Jogador *novosDados = new Jogador[novaCapacidade];

        for (int i = 0; i < l->tamanho; i++)
            novosDados[i] = l->dados[i];

        delete[] l->dados;
        l->dados = novosDados;
        l->capacidade = novaCapacidade;
    }

    for (int i = l->tamanho; i > pos; i--)
        l->dados[i] = l->dados[i - 1];

    l->dados[pos] = novo;
    l->tamanho++;

    return true;
}

Jogador acessar(const ListaContEst *l, int pos) {
    if (pos < 0 || pos >= l->tamanho)
        return Jogador{"", -1};

    return l->dados[pos];
}

int buscar(const ListaContEst *l, int score) {
    for (int i = 0; i < l->tamanho; i++) {
        if (l->dados[i].score == score)
            return i;
    }

    return -1;
}

bool remover(ListaContEst *l, int pos) {
    if (pos < 0 || pos >= l->tamanho)
        return false;

    for (int i = pos; i < l->tamanho - 1; i++)
        l->dados[i] = l->dados[i + 1];

    l->tamanho--;
    return true;
}

void destruir(ListaContEst *l) {
    delete[] l->dados;
    l->dados = nullptr;
    l->tamanho = 0;
    l->capacidade = 0;
}

void imprimir_ListaContEst(const ListaContEst *l) {
    if (l->tamanho == 0) {
        std::cout << "Lista vazia.\n";
        return;
    }

    for (int i = 0; i < l->tamanho; i++) {
        std::cout << "Nome: " << l->dados[i].nome_jogador
                  << ", Score: " << l->dados[i].score
                  << '\n';
    }
}

int lista_para_vetor(ListaContEst *l, Jogador vetor[]) {
    if (l->tamanho == 0)
        return -1;

    for (int i = 0; i < l->tamanho; i++)
        vetor[i] = l->dados[i];

    return l->tamanho;
}

double ordena_vetor_pelo_score_bubble_sort(
    Jogador vetor[], int tamanhoVetor
) {
    Timer t;
    timer_iniciar(&t);

    for (int k = 0; k < tamanhoVetor - 1; k++) {
        bool foiTrocado = false;

        for (int i = 0; i < tamanhoVetor - 1; i++) {
            if (vetor[i].score < vetor[i + 1].score) {
                Jogador aux = vetor[i];
                vetor[i] = vetor[i + 1];
                vetor[i + 1] = aux;
                foiTrocado = true;
            }
        }

        if (!foiTrocado)
            break;
    }

    return timer_parar(&t);
}

// Usar somente quando houver pelo menos dez registros.
void imprime_dez_primeiros(Jogador vetor[]) {
    std::cout << "RANKING (pelo score)\n";

    for (int i = 0; i < 10; i++) {
        std::cout << i + 1
                  << ". Nome: " << vetor[i].nome_jogador
                  << ", Score: " << vetor[i].score
                  << '\n';
    }
}

void imprime_de_1_a_9(Jogador vetor[], int tamanhoVetor) {
    std::cout << "RANKING (pelo score)\n";

    for (int i = 0; i < tamanhoVetor; i++) {
        std::cout << i + 1
                  << ". Nome: " << vetor[i].nome_jogador
                  << ", Score: " << vetor[i].score
                  << '\n';
    }
}