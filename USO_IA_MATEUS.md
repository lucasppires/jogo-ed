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
