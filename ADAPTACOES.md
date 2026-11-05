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
12. Foi criada buscarPorCodigo, que recebe apenas o código e retorna o nó encontrado ou nullptr.
13. Foi criada sortearPedido, que recebe a raiz e argv, sorteia um código e retorna const Pedido *, sem remover o pedido nem copiar os nós da receita. Retorna nullptr se não conseguir obter um pedido.

Pendente no sorteio: substituir a contagem de linhas a cada chamada e o intervalo de 1 até a quantidade de registros por informações dos códigos disponíveis; integrar a consulta à hash antes da AVL.

Alterações no TAD Fila (04/11/2026):
1. Foi criada a struct Cliente em pedido.hpp, com id e paciencia restante.
2. O dado dos nós passou de Produto para Cliente, para representar a ordem de atendimento.
3. As funções enfileira e desenfileira foram adaptadas para receber e devolver Cliente.
4. Foi criada criarClientes, que gera os identificadores, define a paciência inicial e enfileira todos os clientes. Retorna false se uma inserção falhar.
5. Foi criada clienteDaFrente, que retorna um ponteiro para o cliente sem removê-lo, permitindo consultar e atualizar sua paciência. Retorna nullptr se a fila estiver vazia.
6. Foi criada destruir para esvaziar a fila usando desenfileira, liberando os clientes restantes.

Integração dos clientes ao jogo (04/11/2026):
1. A função novoJogo passou a preparar uma fila própria por partida, com três clientes e paciência provisória sorteada entre 9 e 15, igual para todos na mesma partida.
2. O cliente da frente é consultado e recebe um pedido sorteado da AVL, exibindo identificador, paciência, código e receita.
3. A fila é liberada ao retornar da função, inclusive em falhas de criação ou obtenção do pedido.
4. A raiz da AVL e argv são passados à função novoJogo pela opção Novo jogo do menu.

Pendente: implementar o atendimento, o desconto de paciência e a retirada dos clientes atendidos. A função atual apenas prepara e exibe o primeiro atendimento.

Alterações no TAD Pilha, em andamento (04/11/2026):
1. O dado do nó passou de Produto para Ingrediente, para representar o hambúrguer.
2. A função empilha passou a receber um Ingrediente.

Pendente: adaptar desempilha e topo, que ainda usam Produto, incluir a definição de Ingrediente no cabeçalho e distinguir o nome do nó da pilha do nó da fila.

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

