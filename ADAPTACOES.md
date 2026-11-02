# Adaptações realizadas nas estruturas que nos foram dadas

Primeiramente, transformaram-se os códigos do moodle em C para C++ (.c para .cpp). Em seguida, adaptou-se o conteúdo do código, pq apesar de C ser um subconjunto de C++, é necessário adaptar alguns pontos do código. Por exemplo, malloc (em C) e new (em C++).

Adaptações no TAD AVL:

1. Foi criada a struct Pedido, com código e receita.
2. O campo dado de NodoAvl passou de int para Pedido.
3. A função criarNodo agora recebe const Pedido & e armazena o pedido completo no nó.
4. As funções avlBuscar, avlInserir e avlRemover agora recebem Pedido e comparam seu código.
5. A remoção com dois filhos copia o pedido completo do sucessor.
6. A função avlEmOrdem agora imprime o código e percorre a lista de ingredientes da receita.
7. O carregamento monta os pedidos e os insere na AVL antes do menu.
8. A destruição da AVL foi incluída em liberar_recursos.
9. A struct Pedido foi movida para pedido.hpp, e receita passou de string para ListaEnc.
10. A função avlDestruir agora libera a lista da receita antes de apagar cada nó.
11. A função avlRemover também libera a receita removida. No caso de dois filhos, transfere a lista do sucessor e deixa seu ponteiro nulo para evitar liberar a mesma lista duas vezes.

Alterações no TAD LISTA CONT EST:
1. A struct ListaContEst agora possui como atribudo um array da struct Jogador, definida no início do .hpp. Não é mais um vetor de produtos.
2. A função inserir recebe como parâmetro um Jogador, não mais um Produto.
3. A função acessar foi modificada também, mudei seu retorno: agora é um Jogador.
4. A função buscar também teve seu corpo modificado, para que compilasse
5. Foi adicionado o campo capacidade a struct ListaContEst, pois assim seu limite de jogadores fica flexível.
6. Em vez de um vetor de jogadores com capacidade fixa, troquei para um ponteiro para um vetor de jogadores sem tamanho prévio, mais flexível.
7. A inicialização da ListaContEst agora também atribui um valor de início ao campo de capacidade da struct, definido pela constante CAPACIDADE. Atualmente esse valor é 50.
8. A função inserir na ListaContEst agora não retorna mais false quando a lista esta cheia, mas sim dobra a capacidade da lista, dinamicamente.
9. A função destruir agora também anula o ponteiro pro vetor e zera a capacidade.
10. Foi criada a função para imprimir uma ListaContEst

Alterações no TAD Lista Enc:
1. Em vez de produto, os nodos agora contém ingredientes, em vez de produtos.
2. Nodo se chama NodoReceita.
3. Todas as funções foram alteradas, de forma com que tudo que referenciava produtos agora referencia ingredientes.
4. Também alguns pontos foram otimizados para C++ (new, cout, etc).
5. A busca e a remoção identificam ingredientes pelo símbolo (char), em vez do código de produto.
6. As inserções usam new (std::nothrow) para permitir verificar falhas de alocação.

Organização dos módulos:
1. O antigo módulo lista foi separado em listacontest.hpp/.cpp para o histórico e listaenc.hpp/.cpp para as receitas.
2. Os includes e o comando de compilação foram atualizados para os novos arquivos, incluindo ingredientes.cpp.

Cadastro de ingredientes:
1. Foi criada a struct Ingrediente, com nome, símbolo, perecível, requer_preparo e validade_turnos.
2. Os tipos de ingredientes foram definidos como constantes em ingredientes.hpp.
3. A função buscarIngrediente retorna um ponteiro constante para o ingrediente do símbolo recebido, ou nullptr se ele for inválido.

Carregamento das receitas:
1. A função montarReceita converte as letras em nós, inserindo no final para preservar a ordem de montagem.
2. Cada pedido tem sua lista inicializada e preenchida antes da inserção na AVL.
3. Em símbolo inválido ou falha de inserção na lista, a receita parcial é destruída e a carga retorna erro.
4. Códigos repetidos são verificados antes da montagem, evitando criar listas que não seriam armazenadas. O primeiro pedido do código é preservado.
5. A contagem de registros lidos inclui os repetidos e é diferente da quantidade de nós inseridos.

Verificação realizada:
1. A carga foi conferida com três pedidos, verificando códigos em ordem crescente, ingredientes na ordem das receitas e abertura do menu.

Alterações no Merge Sort
1. Foi adaptado para C++;
2. Agora as três funcoes que compoem o mergeSort (merge, mergeSortRec e mergeSort) foram adaptadas para receber e ordenar um vetor da struct Jogador. Isso porque queremos ordenar o historico em ordem decrescente, para imprimir o top 10 melhores escores.
3. A funcao mergeSort também registra o tempo de execucao e retorna uma variavel do tipo doublefloat indicando o tempo.

