#ifndef MEDICOES_HPP
#define MEDICOES_HPP

#include <iostream>

using namespace std;
#include <fstream>
#include <string>

struct Metricas{
    int nosInseridos = 0;
    int alturaAVL = 0;
    int rotacoes = 0 ;
    double tempoCarga = 0.0f;

    int entradasHistorico = 0;

    int totalComparacoes = 0;
    int totalBuscas = 0;
    double tempoBuscas = 0.0f;

    int tamanhoHash = 0;
    int ocupadasHash = 0;
    int hits = 0;
    int misses = 0;
    int colisoes = 0;

    int tamanhoOrdenacao = 0;
    double tempoOrdenacao = 0.0;
};

extern Metricas met;   // definida em main.cpp

bool iniciaLog(const string& caminho, const Metricas& m);

bool geraRelatorio(const string& caminho, const Metricas& m);


bool registraOrdenacao(const string& caminho, long tamanho, const string& algoritmo, double tempo);

void zeraMetricasPartida(Metricas& m);

#endif