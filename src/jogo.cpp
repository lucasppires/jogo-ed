#include <iostream>
#include <iomanip>

using namespace std;
#include <string>
#include "jogo.hpp"
#include "fila.hpp"
#include "avl.hpp"
#include "pedido.hpp"
#include "timer.hpp"
#include "listacontest.hpp"
#include "funcoes_menu.hpp"
#include <random>
#include <stdexcept>
#include "preparo.hpp"
#include <fstream>
#include <cstring>
#include "avl.hpp"
#include "hash.hpp"
#include "heap.hpp"
#include "pilha.hpp"
#include "hamburguer.hpp"
#include "medicoes.hpp"
#include "timer.hpp"
#include "sortings.hpp"




#define N_MAX_CLIENTES 100
#define N_CLIENTES 3



// essa funcao deve rodar no inicio de cada turno
void removeEstragadosHeap(int turnoAtual, FilaPrioridade *carnes, FilaPrioridade *ovos, FilaPrioridade *bacons)
{
    removeIngredienteEstragado(turnoAtual, carnes);
    removeIngredienteEstragado(turnoAtual, ovos);
    removeIngredienteEstragado(turnoAtual, bacons);
}




const Pedido *obterPedido(NodoAvl *raiz, TabelaEnc *cache, int codigo, Metricas &met) 
{
    // primeiro procura na hash
    const Pedido *pedido = encBuscar(cache, codigo);

    if (pedido != nullptr) return pedido;

    int comparacoes = 0;
    Timer t;
    timer_iniciar(&t);

    // Se nao encontrou na hash, procura na AVL.
    NodoAvl *no = buscarPorCodigo(raiz, codigo, comparacoes);

    // acumula so o tempo da busca na AVL, deixando a consulta da hash fora
    met.tempoBuscas += timer_parar(&t);
    met.totalBuscas++;
    met.totalComparacoes += comparacoes;

    if (no == nullptr) return nullptr;

    // Guarda a referencia no cache para consultas futuras.
    encInserir(cache, codigo, &no->dado);

    return &no->dado;
}

// const pq o pedido sorteado nao deve ser modificado
const Pedido *sortearPedido(NodoAvl *raiz, TabelaEnc *cache, Metricas &met)
{
    if (raiz == nullptr || cache == nullptr || cache->m <= 0)
        return nullptr;

    // Encontra o menor e o maior codigo presentes na AVL.
    const NodoAvl *menor = raiz;
    const NodoAvl *maior = raiz;

    while (menor->esq != nullptr)
        menor = menor->esq;

    while (maior->dir != nullptr)
        maior = maior->dir;

    const Pedido *pedido = nullptr;

    do
    {
        int codigo_sorteado = numero_aleatorio(menor->dado.cod, maior->dado.cod);

        // Consulta a hash e busca na AVL somente no miss.
        pedido = obterPedido(raiz, cache, codigo_sorteado, met);

        // Repete se o codigo sorteado nao existir.
    } while (pedido == nullptr);

    return pedido;
}



int numero_aleatorio(int minimo, int maximo)
{
    if (minimo > maximo)
        throw invalid_argument("Intervalo invalido");

    // static mantem o gerador entre chamadas, sem reiniciar a sequencia a cada sorteio
    static mt19937 gerador(random_device{}());
    uniform_int_distribution<int> intervalo(minimo, maximo);

    return intervalo(gerador);
}

const char *stringParaCharPtr(const string &s)
{
    return s.c_str();
}

// teremos que trocar o nome pra argv[2]. FEITO!
void gravaJogoNoHistorico(int score, ListaContEst *lista_historico, const char* nomeArqHistorico){
    ofstream arq(nomeArqHistorico, ios::app);
    if (!arq.is_open()) return;

    string nome;

    bool verificacao = true;

    while(verificacao == true){
        cout << "Nome: ";
        getline(cin >> ws, nome);   // ws descarta o '\n' que sobrou de leituras anteriores


        const char*nomeVerificado = stringParaCharPtr(nome);

        if (strlen(nomeVerificado) <= 20)
            verificacao = false;

        else 
            cout << "Insira um nome com no maximo 20 caracteres.\n";
    }

    arq << nome << '\n';                // linha 1: nome
    arq << score << '\n';               // linha 2: score

    Jogador novo;
    novo.nome_jogador = nome;      // ajuste aos campos reais do seu struct Jogador
    novo.score = score;
    inserir(lista_historico, novo, lista_historico->tamanho);   // posição = fim

}

// usa as mesmas larguras em todas as linhas para alinhar as colunas
static void mostrarItemEstoque(const Ingrediente &ingrediente,
                               const string &quantidade,
                               const string &situacao,
                               const char *corSituacao)
{
    cout << "  " << setw(8) << ingrediente.simbolo
         << ingrediente.cor << setw(22) << ingrediente.nome << cores::RESET
         << corSituacao << setw(12) << quantidade
         << situacao << cores::RESET << '\n';
}

static void mostrarPerecivel(const Ingrediente &ingrediente,
                             const FilaPrioridade *estoque,
                             int turnoAtual)
{
    string situacao = "Sem unidades prontas";
    const char *corSituacao = cores::CINZA;
    int turnoVencimento;

    if (fpMinimo(estoque, &turnoVencimento)) {
        int turnosRestantes = turnoVencimento - turnoAtual;
        situacao = "Vence em " + to_string(turnosRestantes) + " turno(s)";
        corSituacao = cores::VERDE_CLARO;

        // destaca a unidade que precisa ser usada antes do proximo turno
        if (turnosRestantes <= 1) {
            corSituacao = cores::VERMELHO_CLARO;
        }
    }

    mostrarItemEstoque(ingrediente, to_string(estoque->tamanho),
                       situacao, corSituacao);
}

static void mostrarEstoque(const FilaPrioridade *carnes,
                           const FilaPrioridade *ovos,
                           const FilaPrioridade *bacons,
                           const int quantidadesNaoPereciveis[],
                           int turnoAtual)
{
    const auto formatoAnterior = cout.flags();
    cout << left
         << cores::AZUL_CLARO
         << "\n  ESTOQUE  |  TURNO " << turnoAtual << '\n'
         << "  --------------------------------------------------------------\n"
         << cores::RESET
         << "  " << setw(8) << "Codigo" << setw(22) << "Ingrediente"
         << setw(12) << "Quantidade" << "Situacao\n";

    cout << cores::CIANO_CLARO << "\n  PERECIVEIS PREPARADOS\n" << cores::RESET;
    mostrarPerecivel(CARNE, carnes, turnoAtual);
    mostrarPerecivel(OVO_FRITO, ovos, turnoAtual);
    mostrarPerecivel(BACON, bacons, turnoAtual);

    cout << cores::CIANO_CLARO << "\n  PREPARADOS SEM VENCIMENTO\n" << cores::RESET;
    const Ingrediente *naoPereciveis[] = {
        &QUEIJO_SUICO, &QUEIJO_CHEDDAR, &CEBOLA, &TOMATE
    };

    // as posicoes acompanham a ordem usada no vetor de quantidades
    for (int i = 0; i < 4; i++) {
        string situacao = "Pronto para usar";
        const char *corSituacao = cores::VERDE_CLARO;

        if (quantidadesNaoPereciveis[i] == 0) {
            situacao = "Precisa preparar";
            corSituacao = cores::CINZA;
        }

        mostrarItemEstoque(*naoPereciveis[i],
                           to_string(quantidadesNaoPereciveis[i]),
                           situacao, corSituacao);
    }

    cout << cores::CIANO_CLARO << "\n  SEM PREPARO\n" << cores::RESET;
    const Ingrediente *ilimitados[] = {&PAO, &KETCHUP, &MOSTARDA, &PICLES, &ALFACE};
    for (const Ingrediente *ingrediente : ilimitados) {
        mostrarItemEstoque(*ingrediente, "Ilimitada", "Pronto para usar",
                           cores::VERDE_CLARO);
    }

    cout << cores::AZUL_CLARO
         << "  --------------------------------------------------------------\n"
         << cores::RESET
         << "  Vencimento exibido: unidade mais proxima de vencer.\n"
         << "  Consultar o estoque nao gasta turno.\n\n";
    cout.flags(formatoAnterior);
}

// mostra o trofeu e o total de clientes atendidos ao vencer a partida
static void mostrarVitoria(int numeroClientes)
{
    pula_linha(2);
    
    cout << cores::VERDE_CLARO
         << "\n\n  ==================================================\n"
         << cores::AMARELO_CLARO
         << "                     __________\n"
         << "                    '._      _.'\n"
         << "                  (   |      |   )\n"
         << "                   '._|      |_.'\n"
         << "                      '.___.'\n"
         << "                        | |\n"
         << "                      __| |__\n"
         << "                     [_______]\n\n"
         << cores::VERDE_CLARO
         << "                       VITORIA!\n\n"
         << cores::BRANCO_CLARO
         << "       Todos os clientes foram atendidos!\n"
         << "       Voce concluiu seu turno no Dado Burger.\n\n"
         << cores::CIANO_CLARO
         << "       Clientes atendidos: " << numeroClientes << '\n'
         << cores::VERDE_CLARO
         << "  ==================================================\n"
         << cores::RESET;
}

void novoJogo(NodoAvl *raiz, TabelaEnc *cache, int &estado_menu, char *argv[], PilhaEnc *p, FilaPrioridade *carnes, FilaPrioridade *ovos, FilaPrioridade *bacons, int turnoAtual, int quantidadesPereciveisDisponiveis[], Jogador *player, Metricas &met, ListaContEst *lista_historico, int dificuldade)
 {
    if (raiz == nullptr)
    {
        cout << "Nao existem pedidos para iniciar a partida.\n";
        return;
    }

    FilaEnc clientes; //inicializamos a fila de clientes
    inicializa(&clientes);

    int numeroClientes = N_CLIENTES; // Número de clientes a serem criados

    // Valores provisorios: tres clientes com paciencias aleatorias.
    int pacienciaInicial[N_MAX_CLIENTES]; //vetor do tamanho max

    for (int i = 0; i < numeroClientes; i++) //para cada cliente...
    {
        // sorteia um pedido e guarda na variavel
        const Pedido *pedidoAtual = sortearPedido(raiz, cache, met);

        if (pedidoAtual == nullptr) // Se não houver pedidos disponíveis
        {
            cout << "Nao foi possivel obter um pedido.\n";
            destruir(&clientes);
            return;
        }

        // vetor de numeros aleatorios, sorteamos uma paciencia para cada cliente, mas os valores podem se repetir

        pacienciaInicial[i] = conta_turnos_pedido(&pedidoAtual->receita);

        if (dificuldade == FACIL)
        {
             pacienciaInicial[i] += 4; //usamos essa funcao para contar o numero minimo de turnos e somamos 4, para nao ser tao dificil tb
        }
        else if (dificuldade == NORMAL)
        {
            pacienciaInicial[i] += 2;
        }
        else if (dificuldade == DIFICIL)
        {
            pacienciaInicial[i] += 0;
        }
        
        // criamos o cliente
        // o cliente guarda a referencia do pedido, cuja receita continua pertencendo a AVL
        Cliente cliente_atual = criarCliente(i+1, pacienciaInicial[i], pedidoAtual);

        // enfileiramos o cliente na fila
        if (!enfileira(&clientes, cliente_atual))
        {
            cout << "Erro ao enfileirar os clientes.\n";
            destruir(&clientes);
            return;
        }
    }

    cout << "Partida iniciada com " << tamanho(&clientes) << " clientes.\n";

    turnoAtual = 1;

    player->score = 0;

    bool saida_voluntaria = false;

    // LAÇO DO JOGO
    while (!estaVazia(&clientes))
     {     
        Cliente *atual = clienteDaFrente(&clientes);



        if (atual->paciencia_restante == 0 || saida_voluntaria == true) //gameover ou saida
        {
            esvaziarPilha(p);


            if (atual->paciencia_restante == 0)
            {
                pula_linha(2);
                cout << cores::VERMELHO << "GAME OVER" << cores::RESET << " - A paciencia do cliente acabou! Ele iniciou uma campanha de cancelamento contra o Dado Burguer :( ";
            }
            
            break;  
        }

        pula_linha(2);

        cout << cores::LARANJA << "\nTurno " << turnoAtual << cores::RESET;

        if (atual->paciencia_restante == 1)
        {
            cout << " (ultimo!)\n";
        }
        else
        {
           pula_linha(1);
        }

        removeEstragadosHeap(turnoAtual, carnes, ovos, bacons);

        if (atual != nullptr) // Se houver clientes na fila
        {
            const Pedido *pedidoAtual = atual->pedido_cliente; //atribui o pedido do cliente ao pedido atual

            if (pedidoAtual == nullptr)
            {
                cout << "Cliente sem pedido associado.\n";
                destruir(&clientes);
                return;
            }

            cout << "\nCliente: " << atual->id << '\n';
            cout << "Paciencia restante: "<< atual->paciencia_restante << " turnos.\n"; 

            cout << "Pedido: " << pedidoAtual->cod << '\n';
            imprimir(&pedidoAtual->receita);

            // A montagem do hamburguer sera implementada aqui.

            desenhar_hamburguer(p);

            int opcao;
            cout << "\nInforme a opcao desejada:\n"
                    << "1 - Adicionar ingrediente ao hamburguer\n"
                    << "2 - Remover ingrediente\n"
                    << "3 - Enviar pedido\n"
                    << "4 - Preparar ingrediente perecivel\n"
                    << "5 - Preparar ingrediente nao perecivel\n"
                    << "6 - Consultar estoque\n"
                    << "7 - Sair\n";
                    
            
            string entrada;

            while (true)  //equivale ao cin >> opcao, mas o cin da erro se for digitado um caractere no lugar de um int
            {
                if (!(cin >> entrada)) {
                    esvaziarPilha(p);
                    destruir(&clientes);
                    return;
                }

                if (entrada.size() == 1 && entrada[0] >= '1' && entrada[0] <= '7') {
                    opcao = entrada[0] - '0';
                    break;
                }

                if (entrada == "0") {
                    opcao = 0;
                    break;
                }

                cout << "Opcao invalida! Escolha de 1 a 7: ";
            }

            switch (opcao) {
                case 1: {
                    char adicionado;
                    cout << "Informe o codigo do ingrediente que queres adicionar: " << endl;
                    cin >> adicionado;

                    const Ingrediente *ing = buscarIngrediente(adicionado);
                    if (ing == nullptr) {
                        cout << "Ingrediente invalido" << endl;
                        turnoAtual--;  //como uma operacao invalida nao gasta um turno, e em todo laço é acrescentado 1 ao turno, diminuimos 1 aqui para corrigir
                        atual->paciencia_restante++; //mesma coisa do turno
                    }
                    else if (ing->perecivel) {
                        // carne, ovo, bacon: so adiciona se tiver na heap (e remove de la)
                        usaIngredientePerecivel(adicionado, carnes, ovos, bacons, p);
                    }
                    else {
                        // resto: infinitos ou com contador de estoque
                        usaIngredienteNaoPerecivel(adicionado, quantidadesPereciveisDisponiveis, p);
                    }
                    break;
                }

                case 2:
                    remover_ingrediente(p);
                    break;

                case 3:
                case 0:  //passa de fase na hora
                    if (opcao == 0 || corrige_pedido(p, &pedidoAtual->receita)) {
                        if (opcao == 3) {
                            cout << cores::VERDE_CLARO << "Pedido correto!" << cores::RESET << endl;
                        }

                        Cliente atendido;
                        desenfileira(&clientes, &atendido);
                        esvaziarPilha(p);

                        player->score += atendido.paciencia_restante * (10*((float) dificuldade/2)); //se é facil mult por 1; normal mult por 1.5 e difiil mult por 2

                        cout << "Cliente " << atendido.id
                             << " foi atendido e saiu da fila." << endl;
                        continue; //pula todo o resto do laço do while
                    }

                    cout << "Montaste o hamburguer incorretamente! O cliente pediu para falar com o gerente do restaurante!" << endl;

                    // turnoAtual--;  //como enviar nao gasta um turno, e em todo laço é acrescentado 1 ao turno, diminuimos 1 aqui para corrigir
                    // atual->paciencia_restante++; //mesma coisa do turno

                    if (atual->paciencia_restante <= 0) 
                    {
                        Cliente removido;
                        desenfileira(&clientes, &removido);
                        esvaziarPilha(p);
                        cout << "Cliente " << removido.id << " perdeu a paciencia e foi comer no xis do outro lado da rua :( " << endl;
                        continue; 
                    }
                    break;

                case 4:
                    prepararIngredientePerecivel(turnoAtual, carnes, ovos, bacons);
                break;
                    
                case 5:
                    prepararIngredienteNaoPerecivel(quantidadesPereciveisDisponiveis);
                break;

                case 6:
                    mostrarEstoque(carnes, ovos, bacons, quantidadesPereciveisDisponiveis, turnoAtual);

                    pula_linha(1);
                    cout << cores::AMARELO << "Aperte qualquer tecla e depois ENTER para voltar ao menu de acoes" << cores::RESET << endl;

                    char qqrtecla;

                    cin >> qqrtecla;

                    turnoAtual--;  //como consultar estoque nao gasta um turno, e em todo laço é acrescentado 1 ao turno, diminuimos 1 aqui para corrigir
                    atual->paciencia_restante++; //mesma coisa do turno
                break;

                case 7:
                    turnoAtual--;  //como sair nao gasta um turno, e em todo laço é acrescentado 1 ao turno, diminuimos 1 aqui para corrigir
                    atual->paciencia_restante++; //mesma coisa do turno
                    saida_voluntaria = true;
                break;
                    
                default:
                    cout << "Opcao invalida" << endl;
                    turnoAtual--;  //como uma operacao invalida nao gasta um turno, e em todo laço é acrescentado 1 ao turno, diminuimos 1 aqui para corrigir
                    atual->paciencia_restante++; //mesma coisa do turno
                break;

            }

            

        }
            // O cliente continua na fila durante o atendimento.

        turnoAtual++;

        atual->paciencia_restante = atual->paciencia_restante - 1; 
        
    }

    if (estaVazia(&clientes) == true)
    {
        mostrarVitoria(numeroClientes); //tela de vitoria
    }

    pula_linha(1);
    cout << cores::VERDE_CLARO << "Sua pontuacao: " << player->score << cores::RESET;
    pula_linha(1);

    gravaJogoNoHistorico(player->score, lista_historico, argv[2]);
    exibirEstatisticasHash(cache, &met);
    geraRelatorio("data/medicoes.log", met);
    destruir(&clientes);

}
