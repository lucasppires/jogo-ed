
#include "medicoes.hpp"

using namespace std;
#include <fstream>
#include <iostream>
#include <iomanip>
#include <sstream>
 
// Monta o texto uma vez so; depois manda o MESMO texto para a tela e para o log.

 
static string textoRelatorio(const Metricas& m) {
    ostringstream s;
    s << fixed;
 
    // TODO: conferir se as contas batem com o que voces acumularam
    double media  = (m.totalBuscas > 0) ? (double)m.totalComparacoes / m.totalBuscas : 0.0;
    double lambda = (m.tamanhoHash > 0) ? (double)m.ocupadasHash / m.tamanhoHash : 0.0;
    long consultas = m.hits + m.misses;
    double taxa   = (consultas > 0) ? 100.0 * m.hits / consultas : 0.0;
 
    s << "=== RELATORIO DE DESEMPENHO ===\n";
 
    s << "-- AVL: carregamento --\n";
    s << "Nos inseridos: " << m.nosInseridos << "\n";
    s << "Altura resultante: " << m.alturaAVL << "\n";
    s << "Rotacoes (insercao): " << m.rotacoes << "\n";
    s << "Tempo de carregamento: " << setprecision(6) << m.tempoCarga << " s\n";
 
    s << "-- Historico: carregamento --\n";
    s << "Entradas carregadas: " << m.entradasHistorico << "\n";
 
    s << "-- AVL: buscas durante a partida --\n";
    s << "Total de buscas: " << m.totalBuscas << "\n";
    s << "Total de comparacoes: " << m.totalComparacoes << "\n";
    s << "Media de comparacoes por busca: " << setprecision(2) << media << "\n";
    s << "Tempo total acumulado: " << setprecision(6) << m.tempoBuscas << " s\n";
 
    s << "-- Tabela hash --\n";
    s << "Tamanho (m): " << m.tamanhoHash << "\n";
    s << "Entradas ocupadas (n): " << m.ocupadasHash << "\n";
    s << "Fator de carga (lambda): " << setprecision(2) << lambda << "\n";
    s << "Total de hits: " << m.hits << "\n";
    s << "Total de misses: " << m.misses << "\n";
    s << "Taxa de acerto: " << setprecision(1) << taxa << "%\n";
    s << "Total de colisoes: " << m.colisoes << "\n";

    s << "-- Ordenacao do historico (ao acessar Historico) --\n";
    s << "Tamanho: " << m.tamanhoOrdenacao << " entradas\n";
    s << "Merge Sort: " << setprecision(6) << m.tempoOrdenacao << " s\n";
 
    s << "================================\n\n";
    return s.str();
}
 
bool iniciaLog(const string& caminho, const Metricas& m) {
    ofstream log(caminho);                  // SEM app: apaga e recria a cada execucao
    if (!log) {
        cerr << "Erro ao criar " << caminho << "\n";
        return false;
    }

    log << fixed;
    log << "=== MEDICOES APOS O CARREGAMENTO ===\n";
    log << "-- AVL: carregamento --\n";
    log << "Nos inseridos: " << m.nosInseridos << "\n";
    log << "Altura resultante: " << m.alturaAVL << "\n";
    log << "Rotacoes (insercao): " << m.rotacoes << "\n";
    log << "Tempo de carregamento: " << setprecision(6) << m.tempoCarga << " s\n";
    log << "-- Historico: carregamento --\n";
    log << "Entradas carregadas: " << m.entradasHistorico << "\n";
    log << "====================================\n\n";

    return true;
}
 
bool geraRelatorio(const string& caminho, const Metricas& m) {
    string texto = textoRelatorio(m);
    cout << texto;                          // tela
 
    ofstream log(caminho, ios::app);   // COM app: escreve no final
    if (!log) {
        cerr << "Erro ao abrir " << caminho << "\n";
        return false;
    }
    log << texto;                                // arquivo
    return true;
}
 
bool registraOrdenacao(const string& caminho, long tamanho,
                       const string& algoritmo, double tempo) {
    ostringstream s;
    s << fixed << setprecision(6);
    s << "-- Ordenacao do historico (ao acessar Historico) --\n";
    s << "Tamanho: " << tamanho << " entradas\n";
    s << algoritmo << ": " << tempo << " s\n\n";
 
    cout << s.str();
 
    ofstream log(caminho, ios::app);
    if (!log) {
        cerr << "Erro ao abrir " << caminho << "\n";
        return false;
    }
    log << s.str();
    return true;
}
 
void zeraMetricasPartida(Metricas& m) {
    m.totalBuscas = 0;
    m.totalComparacoes = 0;
    m.tempoBuscas = 0.0;
    m.hits = 0;
    m.misses = 0;
    m.colisoes = 0;
    m.tamanhoOrdenacao = 0;
    m.tempoOrdenacao = 0.0;
    // TODO: se a hash for recriada a cada partida, zere ocupadasHash tambem
}
 
/* ===================== COMO USAR (exemplo no main.cpp) =====================
 
#include "relatorio.hpp"
#include "timer.hpp"
 
Metricas met;   // global ou passada por referencia
 
int main(int argc, char* argv[]) {
    // ... checar argc ...
 
    Timer t;
    timer_iniciar(&t);
    // TODO: carregar AVL (dentro da insercao: met.rotacoes++ em cada rotacao simples)
    met.tempoCarga   = timer_parar(&t);
    met.nosInseridos = // TODO
    met.alturaAVL    = // TODO
 
    // TODO: carregar historico
    met.entradasHistorico = // TODO
 
    iniciaLog("medicoes.log", met);
 
    // loop do menu:
    //   Jogar:
    //     zeraMetricasPartida(met);
    //     ... partida (em cada busca: cronometrar, somar em met.tempoBuscas,
    //                  met.totalBuscas++, met.totalComparacoes += comparacoes) ...
    //     met.tamanhoHash = ...; met.ocupadasHash = ...;
    //     geraRelatorio("medicoes.log", met);
    //
    //   Historico:
    //     copiar o vetor (FORA do cronometro)
    //     timer_iniciar(&t); mergeSort(copia...); double tOrd = timer_parar(&t);
    //     registraOrdenacao("medicoes.log", tamanho, "Merge Sort", tOrd);
}
============================================================================ */