#include <iostream>
#include <string>
#include <fstream>
#include "avl.hpp"
#include "timer.hpp" 

using namespace std;

// Função que retorna o total de pedidos (Código (números) e Receita (string) )
int carregarPedidosAVL(const char *arquivo, NodoAvl **raiz, double *tempo){
    ifstream arq(arquivo);

    if (!arq){  // Se deu problema ao abrir
        cerr << "Nao foi possivel abrir o arquivo.\n";
        return -1;
    }

    int codigo;
    string receita;
    int qtePedidosLidos = 0;

    Timer t;
    timer_iniciar(&t);

    while (arq >> codigo >> receita){
        *raiz = avlInserir(*raiz, codigo, receita);
        qtePedidosLidos++;
    }

    *tempo = timer_parar(&t);
    return qtePedidosLidos;
}

int contarLinhas(const char *nomeArquivo){
        ifstream arq(nomeArquivo);
        if (!arq) return -1;              // arquivo não existe ou não abriu

        int linhas = 0;
        string linha;

        while (getline(arq, linha))
            if (!linha.empty()) linhas++; // ignora linhas em branco
    return linhas;
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        cerr << "Uso: " << argv[0] << " <arquivo_pedidos> <arquivo_historico>\n";
        cerr << "Exemplo: " << argv[0] << " pedidos.txt historico.txt\n";
        return 1;
    }

    const char *arqPedidos   = argv[1];
    const char *arqHistorico = argv[2];

    cout << "Pedidos:   " << arqPedidos << "\n";
    cout << "Historico: " << arqHistorico << "\n";

    cout << "Qte de linhas no arquivo pedidos.txt: " << contarLinhas(arqPedidos) << ".\n";
    cout << "Qte de linhas no arquivo historico.txt: " << contarLinhas(arqHistorico) << ".\n";
    // daqui para frente: carregar os pedidos na AVL e o histórico na lista contígua

    NodoAvl *raiz = nullptr;
    double tempoCarga = 0.0;

    int lidos = carregarPedidosAVL(argv[1], &raiz, &tempoCarga);
    if (lidos < 0) return 1;

    cout << lidos << " pedidos lidos em " << tempoCarga << " s\n";
    return 0;
}