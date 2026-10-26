#include <iostream>
#include <fstream>
#include <string>
using namespace std;


int contarLinhas(const char *nomeArquivo);

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

    return 0;
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

