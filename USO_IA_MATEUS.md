# Uso de IA

1. (Mateus) Pedi pro Claude fazer um Plnao de Tarefas para nos organizarmos e nos dividirmos melhor. Funciona como um checklist.
2. (Mateus) Pedi pro Claude transformar os códigos das estruturas de dados disponíveis no moodle, que eram em C, para C++. Output: 

"O que mudou, em todos os arquivos:

Structs e enum: typedef struct {...} Nome; virou struct Nome {...};, e typedef enum virou enum.

Memória: malloc/free viraram new/delete, e os vetores usam new[]/delete[]. Onde o código original testava se a alocação deu NULL, usei new (std::nothrow), que mantém esse teste funcionando.

Ponteiros nulos: NULL virou nullptr.

Retornos: funções que devolviam 1/0 como sim/não (estaVazia, empilha, encRemover, linInserir…) agora devolvem bool (true/false). As buscas que devolvem um valor ou -1 continuam int.

Headers e casts: <math.h> virou <cmath>, printf virou std::cout e os casts do C viraram static_cast. Na lista, a impressão com 2 casas decimais continua igual.
Includes: apontavam para os nomes antigos ("avl.h", "filaEnc.h"…) e agora usam os .hpp. Os include guards também foram renomeados.

Demos: removi os main de demonstração do avl.cpp e do heap.cpp, porque eles impediriam o programa de compilar junto com o seu main.cpp. Os códigos originais continuam em codigos-moodle/."

3. Pedi ajuda pra ler o historico.txt. vou colar o output da ajuda.

1. O nome tem espaço e por isso o >> falha (é por isso que dá 0)
O historico.txt tem este formato:


Tamires A.
15
O arq2 >> nome lê só até o primeiro espaço, ou seja, "Tamires". Depois o >> score tenta ler "A." como inteiro, falha, e o while termina logo na primeira volta. A solução é usar getline para o nome:


while (getline(arq2, nome) && arq2 >> score){
    arq2.ignore();          // descarta o '\n' que sobra depois do número
    ...
}

4. (Mateus) Teste: Claude Code escrevendo automaticamente neste arquivo.
5. (Mateus) Pedi pro Claude converter o código do Merge Sort (que estava em C) para C++ e colocar em src/sortings.cpp e src/sortings.hpp. O que mudou: malloc/free viraram new (std::nothrow) int[n] / delete[]; as variáveis de laço passaram a ser declaradas no próprio uso (estilo C++); e o mergeSort retorna direto se n <= 1 ou se a alocação falhar.
6. (Mateus) Depois de adaptar o Merge Sort pra ordenar Jogador pelo score, o sortings.hpp parou de compilar ("'Jogador' was not declared in this scope"). Causa: o sortings.hpp usava o struct Jogador sem incluir o lista.hpp, onde ele é definido. Solução: adicionar #include "lista.hpp" no sortings.hpp, logo depois do #define SORTINGS_HPP.
7. (Mateus) Ao compilar o teste_menu deu erro de linkagem: "undefined reference to `mergeSortAdaptado(Jogador*, int)'". Causa: o src/sortings.cpp (onde a função está implementada) não estava no comando do g++. Solução: adicionar src/sortings.cpp na lista de arquivos:

g++ tests/teste_menu.cpp src/funcoes_menu.cpp src/leitura_de_arquivos.cpp src/lista.cpp src/avl.cpp src/timer.cpp src/sortings.cpp -I src -o tests/teste_menu.exe -Wall -std=c++17

8. (Mateus) Pedi ajuda com o src/teste_pilha.cpp (teste da pilha de ingredientes do hambúrguer). Problemas encontrados e soluções:
   - Faltava #include <iostream> e o cout estava com o operador invertido (cout >> em vez de cout <<). O >> é usado com cin.
   - O arquivo não tinha main(), então não dava pra compilar sozinho. Comando de compilação (dentro de src): g++ teste_pilha.cpp pilha.cpp ingredientes.cpp -o teste_pilha
   - O switch que converte a letra no Ingrediente não tinha break em cada case, então qualquer letra válida caía até o default ("caractere invalido"). Solução: break; no fim de cada case (alternativa: usar a função buscarIngrediente, que já existe em ingredientes.cpp).
   - A pilha guardava Produto (cod, nome, preco), que veio do código do moodle. Adaptei pra guardar Ingrediente: o Nodo passou a ter Ingrediente dado, e empilha/desempilha/topo passaram a receber Ingrediente.
   - Depois disso deu "'Ingrediente' does not name a type" no pilha.hpp. Causa: o pilha.hpp usava Ingrediente sem incluir o ingredientes.hpp (nos .cpp o pilha.hpp era incluído antes). Solução: adicionar #include "ingredientes.hpp" no pilha.hpp, logo depois do #define PILHA_HPP.
9. (Mateus) Pedi ao Claude um resumo dos últimos commits do Lucas e ajuda com a função imprimir_hamburguer, do src/teste_pilha.cpp, para imprimir o hambúrguer colorido usando o cores.hpp. O que foi feito e explicado:
   - Sugestão implementada: adicionar o campo const char *cor na struct Ingrediente e incluir o cores.hpp no ingredientes.hpp. Cada constante de ingrediente recebe sua cor como último valor. Como a pilha guarda cópias dessas constantes, a cor vai junto, sem precisar de switch.
   - Impressão: cout << aux->dado.cor << aux->dado.nome << cores::RESET << endl; O RESET no fim da linha evita que a cor vaze para o texto seguinte.
   - Por minha conta, escolhi as cores de cada ingrediente, criei as cores MARROM e LARANJA no cores.hpp e usei using namespace cores no ingredientes.hpp.
   - Dúvida sobre os ponteiros da pilha: eu achava que o prox apontava para cima e que o do topo era nulo. O Claude explicou que, em empilha, novo->prox = p->topo faz cada nodo apontar para o de baixo, então dá para percorrer do topo até a base, e só o nodo da base tem prox nulo. Confirmamos rodando a função com o pilha.cpp e imprimindo o prox de cada nodo.
   - Revisão do código, com pontos apontados e ainda não corrigidos: o "Pao de baixo" é impresso antes do laço, ou seja, aparece em cima do hambúrguer; o comentário no início da função ainda diz que os ponteiros vão para cima; o main ainda não chama imprimir_hamburguer; a linha que verifica o topo em adicionar_ingrediente acessa p->topo->dado mesmo com a pilha vazia.
10. (Mateus) Pedi ao Claude uma pilha de exemplo para testar as funções adicionar_ingrediente, remover_ingrediente, corrige_pedido e imprimir_hamburguer. O que foi feito:
   - O Claude gerou um main de teste com 10 cenários: pilha vazia, adicionar e remover ingrediente, bloqueio depois do pão de cima, letra inválida, pedido certo, ordem errada e quantidade errada. Também gerou uma receita de exemplo (bnqz) e duas funções auxiliares, esvaziar e montar.
   - Por minha conta, levei essas funções para o TAD Pilha (pilha.cpp e pilha.hpp) com os nomes esvaziarPilha e montarPilhaViaSimbolos.
   - Corrigi os pontos da revisão do item 9: a verificação do topo agora usa !estaVazia(p), o comentário errado sobre os ponteiros foi removido, e o main agora chama imprimir_hamburguer, definida antes dele.
   - Dúvida: perguntei onde estava a função montar, e o Claude explicou que ela não existia no meu código, pois tinha sido criada por ele para o teste.
   - Comando de compilação (dentro de src): g++ teste_pilha.cpp pilha.cpp ingredientes.cpp listaenc.cpp -o teste_pilha -Wall -std=c++17
   - Ainda pendente: "Pao de baixo" continua sendo impresso duas vezes em imprimir_hamburguer; montarPilhaViaSimbolos não verifica se buscarIngrediente devolveu nullptr em caso de letra inválida.
11. (Mateus) Perguntei ao Claude o que precisava mudar no src/heap.cpp para operar sobre uma min-heap em vez de max-heap. O que foi explicado e feito:
   - Sugestão implementada: trocar > por < nas três comparações, duas em heapify (a[esq] < a[maior] e a[dir] < a[maior]) e uma em siftUp (a[i] < a[pai]).
   - Fila de prioridade: a lógica não muda, pois ela só chama heapify e siftUp. Apenas renomeei fpMaximo para fpMinimo e fpRemoverMaximo para fpRemoverMinimo.
   - Efeito colateral apontado pelo Claude: com min-heap, o heapSort passa a ordenar em ordem decrescente. O Claude sugeriu inverter o array no final ou remover a função, caso não fosse usada.
   - Por minha conta, coloquei uma chamada a mergeSort no final do heapSort. Na revisão, o Claude confirmou que o resultado fica em ordem crescente, mas apontou que o trabalho do heap sort é descartado e que isso exige O(n) de memória extra.
   - Ainda pendente na revisão: decidir entre inverter o array ou remover o heapSort, que não é chamado em src/; a variável maior em heapify agora guarda o menor; o comentário do heapSort ainda fala em "maximo".
12. (Mateus) Pedi ajuda com a função preparar_ingrediente, no src/teste_heap.cpp. O que foi explicado e feito:
   - cout e endl não funcionavam porque faltava #include <iostream>. O using namespace std não declara esses nomes, só evita escrever std::.
   - Erro na linha de buscarIngrediente: a função retorna const Ingrediente *, e eu guardava em uma variável Ingrediente. Solução: declarar const Ingrediente *preparado, o que também permite testar o ponteiro no if.
   - Dúvidas: o Claude explicou que buscarIngrediente retorna um endereço para poder devolver nullptr em letra inválida e evitar cópia da struct, e que isso é seguro porque as constantes são globais.
   - Sugestões implementadas: calculaTurnoVencimento passou a receber o ponteiro já validado, e o turno de vencimento é inserido com fpInserir na fila de cada perecível.
   - Por minha conta, escrevi a função, com os parâmetros turnoAtual e as três filas e o switch pelo símbolo do ingrediente.
   - Ainda pendente na revisão: tratar ingredientes com preparo não perecíveis e rejeitar os que não precisam de preparo; informar a quem chama se o turno deve ser gasto; o heap.hpp ainda declara fpMaximo e fpRemoverMaximo.
13. (Mateus) Pedi ao Claude uma revisão da divisão do preparo em duas funções, prepararIngredientePerecivel e prepararIngredienePerene, no src/teste_heap.cpp. O que foi feito e apontado:
   - Sugestões implementadas: as funções passaram a retornar bool, para indicar se o preparo deu certo, e os ingredientes não perecíveis passaram a usar contadores de quantidade.
   - Por minha conta, decidi dividir em duas funções e guardar os contadores em um vetor de 4 posições.
   - Ainda pendente na revisão: a função perene retorna true para ingredientes sem preparo (ketchup, por exemplo) sem preparar nada; a função perecível retorna true mesmo quando fpInserir falha; cada função lê o código do ingrediente, então quem chama não sabe qual delas usar sem pedir o código duas vezes (sugestão: ler o código uma vez em prepararIngrediente e passar o ponteiro para as duas); o nome prepararIngredienePerene está sem o "t".
14. (Mateus) Depois das revisões dos itens 11 e 13, corrigi alguns pontos no src/heap.cpp e no src/teste_heap.cpp e pedi ao Claude para registrar as adaptações no ADAPTACOES.md e as ajudas neste arquivo. O que foi feito:
   - No heapSort, troquei a chamada a mergeSort pela inversão do vetor sugerida pelo Claude, que custa O(n) e não usa memória extra.
   - Em prepararIngredientePerecivel, a função agora retorna false quando fpInserir falha.
   - Em prepararIngredientePerene, adicionei a verificação de requer_preparo, então ingredientes como o ketchup retornam false. Essa foi uma alternativa minha ao default no switch sugerido pelo Claude. Também corrigi o nome da função.
   - O Claude conferiu o código atual e escreveu as seções de Heap e de preparo de ingredientes no ADAPTACOES.md.
   - Ainda pendente: cada função de preparo continua lendo o código por conta própria; o heap.hpp ainda declara fpMaximo e fpRemoverMaximo; o include de sortings.hpp em heap.cpp não é mais necessário; a variável maior em heapify agora guarda o menor; o comentário do heapSort ainda fala em "maximo"; o main de teste_heap.cpp ainda está vazio, então as funções de preparo não foram testadas.
15. (Mateus) Tirei uma dúvida sobre o heap, pedi ajuda para melhorar a função removeIngredienteEstragado e pedi uma revisão do src/teste_heap.cpp. O que foi explicado e feito:
   - Dúvida: perguntei para que serve o int *valor de fpRemoverMinimo. O Claude explicou que é um parâmetro de saída: o return indica se a remoção deu certo e o ponteiro entrega o valor removido, sem precisar de um valor especial de erro, como -1, que poderia ser confundido com um dado válido.
   - Problema na minha versão recursiva: ela lia dados[0] sem verificar se o heap estava vazio. Quando todas as unidades venciam, o valor antigo continuava em dados[0], fpRemoverMinimo não removia mais nada e a recursão nunca terminava. Além disso, faltava return no else.
   - Sugestão implementada: troquei a recursão por um while (fpMinimo(turnosDeVencimento, &vencimento) and (vencimento <= turnoAtual)), que para quando o heap esvazia ou quando o topo ainda não venceu.
   - Sugestão não implementada: o Claude sugeriu retornar um int com a quantidade de unidades removidas. Mantive o retorno bool, mas a função ainda não tem return.
   - Por minha conta, escrevi usaIngredientePerecivel e usaIngredientePerene e resolvi duas pendências do item 14: o heap.hpp agora declara fpMinimo e fpRemoverMinimo, e o include de sortings.hpp saiu do heap.cpp.
   - Revisão: o Claude compilou o código com -Wall -Wextra e executou as funções em um teste temporário fora do projeto. No código atual, a primeira chamada de removeIngredienteEstragado quebra o programa: com -O0 termina com instrução ilegal e com -O2 fica travado. Em uma cópia temporária com os return adicionados, os casos de heap vazio, nenhuma unidade vencida, todas vencidas e situação mista funcionaram.
   - Ainda pendente na revisão: adicionar os return que faltam em removeIngredienteEstragado e usaIngredientePerecivel; o parâmetro turnoAtual não é usado em usaIngredientePerecivel, e o teste confirmou que uma unidade vencida pode ser consumida; cada função continua lendo o código por conta própria; ingredientes sem preparo, como o ketchup, retornam false em usaIngredientePerene, embora tenham quantidade infinita; a mensagem "Deu merda" precisa ser trocada; os comentários do heap.hpp ainda falam em max-heap; a variável maior em heapify agora guarda o menor; o comentário do heapSort ainda fala em "maximo"; o main de teste_heap.cpp ainda está vazio.
16. (Mateus) Pedi ao Claude para completar o src/teste_pilha.hpp a partir do src/teste_pilha.cpp. O que foi feito:
   - O Claude adicionou o include guard (TESTE_PILHA_HPP) e os protótipos de adicionar_ingrediente, remover_ingrediente, corrige_pedido e imprimir_hamburguer. Os includes que eu já tinha colocado foram mantidos, e o ListaEnc usado em corrige_pedido vem pelo pedido.hpp.
   - O Claude compilou o header junto com o .cpp em um arquivo temporário fora do projeto, com -Wall -std=c++17, sem erros nem avisos.
   - Ainda pendente: o teste_pilha.cpp ainda não inclui o teste_pilha.hpp; o main está no teste_pilha.cpp, então ele precisa sair de lá antes de ligar essas funções ao jogo, senão haverá dois main.
