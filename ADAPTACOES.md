# Adaptações realizadas nas estruturas que nos foram dadas

Este arquivo reúne as alterações feitas nos códigos do Moodle e no restante do jogo, **organizadas por estrutura de dado** e, depois, pelos demais módulos. Quando uma alteração envolve mais de uma estrutura, ela aparece em todas as seções correspondentes, para que cada seção possa ser copiada sozinha.

- O título de cada seção informa os dias em que houve mudanças naquela estrutura ou módulo. As alterações iniciais, registradas sem data, não entram nessa lista.
- Dentro de cada seção, os itens estão em ordem cronológica.
- Pendências: ✅ resolvida · ⏳ em aberto · ❔ conclusão não registrada neste arquivo.
- Os nomes de arquivo são os da época do registro (por exemplo, `testemenu.cpp`, `testepilha.cpp` e `testeheap.cpp`).

## Sumário

**Parte 1 — Estruturas de dados**
1. TAD AVL
2. TAD Fila
3. TAD Pilha
4. TAD Lista Contígua Estática (`ListaContEst`)
5. TAD Lista Encadeada (`ListaEnc`)
6. TAD Hash (encadeamento separado)
7. TAD Heap / Fila de prioridade
8. Ordenação (Merge Sort e Heap Sort)

**Parte 2 — Outros módulos**

9. Ingredientes
10. Leitura e gravação de arquivos
11. Medições e `medicoes.log`
12. Partida (`novoJogo`), turnos e paciência
13. Estoque e preparo de ingredientes
14. Organização dos módulos e compilação
15. Pendências em aberto (resumo)

---

## Adaptação geral (C → C++)

1. Os códigos do Moodle em C foram transformados em C++ (.c para .cpp). Em seguida, adaptou-se o conteúdo do código, porque, apesar de C ser um subconjunto de C++, é necessário adaptar alguns pontos. Por exemplo, `malloc` (em C) e `new` (em C++).

---

# Parte 1 — Estruturas de dados

## 1. TAD AVL (`avl.hpp` / `avl.cpp`) — mudanças em 04/11, 06/11, 08/11, 14/11

1. Foi criada a struct `Pedido`, com código e receita.
2. O campo `dado` de `NodoAvl` passou de `int` para `Pedido`.
3. A função `criarNodo` agora recebe `const Pedido` e armazena o pedido completo no nó.
4. As funções `avlBuscar`, `avlInserir` e `avlRemover` agora recebem `Pedido` e comparam seu código.
5. A remoção com dois filhos copia o pedido completo do sucessor.
6. A função `avlEmOrdem` agora imprime o código e percorre a lista de ingredientes da receita.
7. O carregamento monta os pedidos e os insere na AVL antes do menu.
8. A destruição da AVL foi incluída em `liberarrecursos`.
9. A struct `Pedido` foi movida para `pedido.hpp`, e `receita` passou de `string` para `ListaEnc`.
10. A função `avlDestruir` agora libera a lista da receita antes de apagar cada nó.
11. A função `avlRemover` também libera a receita removida. No caso de dois filhos, transfere a lista do sucessor e deixa seu ponteiro nulo, para evitar liberar a mesma lista duas vezes.
12. Foi criada `buscarPorCodigo`, que recebe apenas o código e retorna o nó encontrado ou `nullptr`.
13. Foi criada `sortearPedido`, posteriormente movida para `jogo.cpp` e adaptada para consultar a hash antes da AVL, sem remover o pedido nem copiar os nós da receita (ver itens 23 a 25).
14. No carregamento, cada pedido tem sua lista (receita) inicializada e preenchida antes da inserção na AVL.
15. Códigos repetidos são verificados antes da montagem da receita, evitando criar listas que não seriam armazenadas na AVL. O primeiro pedido de cada código é preservado.
16. A contagem de registros lidos inclui os repetidos e é diferente da quantidade de nós inseridos na AVL.
17. Verificação: a carga foi conferida com três pedidos, verificando códigos em ordem crescente, ingredientes na ordem das receitas e abertura do menu.
18. O cliente da frente da fila recebe um pedido sorteado da AVL, e são exibidos identificador, paciência, código e receita.
19. A raiz da AVL e `argv` passaram a ser passados à função `novoJogo` pela opção Novo jogo do menu.
20. A struct `Cliente` ganhou `pedidocliente`, do tipo `const Pedido *`, que aponta para o pedido guardado na AVL sem duplicar a receita. Destruir a fila não libera os pedidos, que continuam pertencendo à AVL.
21. Foi criada `obterPedido` em `jogo.cpp`, que consulta primeiro a hash; em um miss, busca na AVL e insere no cache a referência encontrada.
22. A função `liberarrecursos` ganhou um parâmetro opcional para a hash, liberando o cache antes da AVL. O valor padrão `nullptr` permite usá-la nos erros anteriores à criação do cache.
23. A função `sortearPedido` foi movida da AVL para `jogo.cpp` e passou a receber a raiz e o cache. A declaração e a chamada foram atualizadas, removendo a versão antiga.
24. O intervalo do sorteio passou a usar o menor e o maior código da árvore, sem reler o arquivo. Códigos inexistentes provocam outro sorteio.
25. O pedido sorteado agora é recuperado por `obterPedido`: hash primeiro e AVL somente no miss.
26. `reequilibrar` passou a receber `int *rotacoes`, com padrão `nullptr`: soma 1 nas rotações simples (LL e RR) e 2 nas duplas (LR e RL). `avlRemover` continua chamando sem contador, então só as rotações da inserção são contadas.
27. `avlInserir` passou a receber `int rotacoes` e repassá-lo nas chamadas recursivas e em `reequilibrar`. O carregamento passa `met.rotacoes`.
28. `buscarPorCodigo` passou a receber `int comparacoes`, somando 1 a cada nó visitado.
29. A altura registrada é `avlAltura(raiz) + 1`, pois `avlAltura` usa -1 para árvore vazia e a especificação usa 0.
30. `obterPedido` e `sortearPedido` passaram a receber `Metricas met`. No miss da hash, `obterPedido` cronometra `buscarPorCodigo` e acumula `totalBuscas`, `totalComparacoes` e `tempoBuscas`.
31. A struct `Metricas` (módulo `medicoes`) guarda os dados do carregamento da AVL e das buscas na AVL, apresentados no Relatório de Desempenho.

## 2. TAD Fila (`fila.hpp` / `fila.cpp`) — mudanças em 04/11, 06/11, 10/11, 15/11

1. Foi criada a struct `Cliente` em `pedido.hpp`, com id e paciência restante.
2. O dado dos nós passou de `Produto` para `Cliente`, para representar a ordem de atendimento.
3. As funções `enfileira` e `desenfileira` foram adaptadas para receber e devolver `Cliente`.
4. Foi criada `criarClientes`, que gera os identificadores, define a paciência inicial e enfileira todos os clientes. Retorna false se uma inserção falhar. (Substituída por `criarCliente`, item 11.)
5. Foi criada `clienteDaFrente`, que retorna um ponteiro para o cliente sem removê-lo, permitindo consultar e atualizar sua paciência. Retorna `nullptr` se a fila estiver vazia.
6. Foi criada `destruir`, para esvaziar a fila usando `desenfileira`, liberando os clientes restantes.
7. A função `novoJogo` passou a preparar uma fila própria por partida, com três clientes e paciência provisória sorteada entre 9 e 15, igual para todos na mesma partida.
8. O cliente da frente é consultado e recebe um pedido sorteado da AVL, exibindo identificador, paciência, código e receita.
9. A fila é liberada ao retornar de `novoJogo`, inclusive em falhas de criação ou obtenção do pedido.
10. A struct `Cliente` ganhou `pedidocliente`, do tipo `const Pedido *`, para associar o cliente ao pedido da AVL sem duplicar a receita.
11. A função `criarClientes` foi substituída por `criarCliente`, que recebe identificador, paciência e ponteiro do pedido e devolve um `Cliente`.
12. O enfileiramento passou a ser feito em `novoJogo`, verificando o retorno de `enfileira`. Destruir a fila não libera os pedidos, que continuam pertencendo à AVL.
13. Cada cliente passou a receber um sorteio próprio de paciência entre 9 e 15; os valores podem se repetir.
14. O pedido é sorteado e associado ao cliente antes de ele ser enfileirado.
15. O atendimento consulta o pedido pelo campo `pedidocliente` do cliente da frente, em vez de manter apenas uma variável separada.
16. A fila parcial é liberada se a obtenção do pedido ou o enfileiramento falhar.
17. O nó da pilha foi renomeado para `NodoPilha`, porque a fila também tem uma struct `Nodo` e o `jogo.cpp` inclui os dois cabeçalhos. O nó da fila continua se chamando `Nodo`.
18. Em `novoJogo`, a paciência inicial de cada cliente passou a ser o custo do seu pedido (`contaturnospedido`) mais 2 turnos de margem, no lugar do sorteio entre 9 e 15.

## 3. TAD Pilha (`pilha.hpp` / `pilha.cpp`) — mudanças em 04/11, 08/11, 10/11, 13/11, 15/11

1. O dado do nó passou de `Produto` para `Ingrediente`, para representar o hambúrguer.
2. A função `empilha` passou a receber um `Ingrediente`.
3. A struct `Ingrediente` ganhou o campo `cor`, do tipo `const char *`, e cada constante de ingrediente passou a ter sua cor. Assim, a cor acompanha as cópias guardadas na pilha.
4. O `ingredientes.hpp` passou a incluir `cores.hpp`, e foram criadas as cores `MARROM` e `LARANJA`.
5. Foi criada `esvaziarPilha`, que desempilha todos os ingredientes, liberando os nós.
6. Foi criada `montarPilhaViaSimbolos`, que esvazia a pilha e empilha os ingredientes de uma string de símbolos, da base para o topo. É usada no teste e supõe que todos os símbolos sejam válidos.
7. Em `testepilha.cpp`, foi criada `imprimirhamburguer`, que percorre a pilha do topo até a base e imprime cada ingrediente na sua cor.
8. A verificação do pão de cima em `adicionaringrediente` passou a usar `estaVazia` antes de acessar `p->topo`, evitando acesso por ponteiro nulo com a pilha vazia.
9. O main de `testepilha.cpp` passou a testar `adicionaringrediente`, `removeringrediente`, `corrigepedido` e `imprimirhamburguer`. A compilação do teste agora precisa de `listaenc.cpp`.
10. A struct `Nodo` da pilha passou a se chamar `NodoPilha`, em `pilha.hpp`, `pilha.cpp` e `testepilha.cpp`, pois a fila também tem uma struct `Nodo` e o `jogo.cpp` inclui os dois cabeçalhos.
11. A função `removeringrediente` passou a retornar true quando a remoção dá certo. Antes, o `else` sem chaves fazia a função retornar false sempre.
12. O main de `testepilha.cpp` ficou entre `#ifdef TESTEPILHAMAIN` e `#endif`, para que as funções possam ser compiladas junto com o `testemenu`. Para testar a pilha sozinha, compila-se com `-DTESTEPILHAMAIN`.
13. A função `novoJogo` passou a receber a pilha do hambúrguer (`PilhaEnc *`), e o `jogo.hpp` passou a incluir `pilha.hpp`, onde `PilhaEnc` é definida.
14. No `testemenu`, cada partida cria e inicializa a pilha e passa seu endereço para `novoJogo`.
15. A cada turno, o jogador pode adicionar ou remover ingrediente do hambúrguer, além de enviar o pedido ou preparar ingredientes.
16. A opção de adicionar ingrediente passou a ler o código uma vez e encaminhá-lo a `usaIngredientePerecivel` ou `usaIngredienteNaoPerecivel`. O estoque é baixado depois que o ingrediente entra na pilha. Ingredientes ilimitados são adicionados diretamente.
17. Em `testepilha.cpp`, foi criada `desenhoingrediente`, que associa o símbolo de cada ingrediente a um padrão de caracteres.
18. A função `desenharhamburguer`, declarada em `testepilha.hpp`, recebe `const PilhaEnc *` e percorre os nós do topo à base sem desempilhar. Cada camada e seu nome são impressos na cor do ingrediente, com restauração da cor do terminal depois do nome.
19. O pão de cima tem um desenho de várias linhas. O pão de baixo é desenhado separadamente, inclusive com a pilha vazia, pois faz parte da base e não ocupa um nó.
20. `novoJogo` chama `desenharhamburguer` na tela da partida. A função `imprimirhamburguer` continua disponível para exibir a versão em texto.

**Pendências**
- ❔ Adaptar `desempilha` e `topo`, que ainda usavam `Produto`, e incluir a definição de `Ingrediente` no cabeçalho.
- ✅ Distinguir o nome do nó da pilha do nó da fila (`NodoPilha`).
- ⏳ Ajustar a impressão do "Pao de baixo" em `imprimirhamburguer`, que aparece no início e no fim do hambúrguer. (A nova `desenharhamburguer` desenha o pão de baixo separadamente.)
- ✅ Levar as funções de `testepilha.cpp` para o jogo.
- ⏳ Chamar `esvaziarPilha` depois de cada partida, para liberar os nós do hambúrguer.

## 4. TAD Lista Contígua Estática (`listacontest.hpp` / `listacontest.cpp`) — mudanças em 10/11, 14/11, 15/11

1. A struct `ListaContEst` agora possui como atributo um array da struct `Jogador`, definida no início do .hpp. Não é mais um vetor de produtos.
2. A função `inserir` recebe como parâmetro um `Jogador`, não mais um `Produto`.
3. A função `acessar` também foi modificada: agora retorna um `Jogador`.
4. A função `buscar` também teve seu corpo modificado, para que compilasse.
5. Foi adicionado o campo `capacidade` à struct `ListaContEst`, para que o limite de jogadores fique flexível.
6. Em vez de um vetor de jogadores com capacidade fixa, passou-se a usar um ponteiro para um vetor de jogadores sem tamanho prévio.
7. A inicialização da `ListaContEst` agora também atribui um valor inicial ao campo `capacidade`, definido pela constante `CAPACIDADE` (atualmente 50).
8. A função `inserir` não retorna mais false quando a lista está cheia: ela dobra a capacidade da lista dinamicamente.
9. A função `destruir` agora também anula o ponteiro para o vetor e zera a capacidade.
10. Foi criada a função para imprimir uma `ListaContEst`.
11. O antigo módulo lista foi separado em `listacontest.hpp/.cpp`, para o histórico, e `listaenc.hpp/.cpp`, para as receitas.
12. Na leitura do histórico, o `'\r'` passou a ser removido do nome antes de copiá-lo para o `Jogador`. Antes, a remoção acontecia depois da cópia, e o nome guardado continuava com o `'\r'`.
13. O `jogo.hpp` ganhou a declaração antecipada `struct ListaContEst;`, pois o `listacontest.hpp` inclui o `jogo.hpp` e incluir o contrário formaria um ciclo.
14. `gravaJogoNoHistorico` passou a receber a `listahistorico` e, além de gravar no arquivo, insere o novo `Jogador` no fim da lista. `novoJogo` recebe a lista do `testemenu` e a repassa.
15. `medirOrdenacaoHistorico` copia a lista para um vetor, fora do intervalo cronometrado, antes de ordená-lo com `mergeSortAdaptado`.
16. A definição de `Jogador` foi movida de `listacontest.hpp` para `jogo.hpp`, pois o tipo é usado na partida e no histórico. A lista continua armazenando registros com nome e pontuação e inclui `jogo.hpp` para acessar a definição.

## 5. TAD Lista Encadeada (`listaenc.hpp` / `listaenc.cpp`) — mudanças em 13/11, 15/11

1. Os nodos agora contêm ingredientes, em vez de produtos.
2. O nodo se chama `NodoReceita`.
3. Todas as funções foram alteradas, de forma que tudo que referenciava produtos agora referencia ingredientes.
4. Alguns pontos foram otimizados para C++ (`new`, `cout` etc.).
5. A busca e a remoção identificam ingredientes pelo símbolo (`char`), em vez do código de produto.
6. As inserções usam `new (std::nothrow)` para permitir verificar falhas de alocação.
7. O antigo módulo lista foi separado em `listacontest.hpp/.cpp`, para o histórico, e `listaenc.hpp/.cpp`, para as receitas.
8. O campo `receita` de `Pedido` passou de `string` para `ListaEnc`.
9. `avlDestruir` libera a lista da receita antes de apagar cada nó, e `avlRemover` libera a receita removida (com dois filhos, transfere a lista do sucessor e anula seu ponteiro).
10. A função `montarReceita` converte as letras em nós, inserindo no final para preservar a ordem de montagem.
11. Cada pedido tem sua lista inicializada e preenchida antes da inserção na AVL.
12. Em símbolo inválido ou falha de inserção na lista, a receita parcial é destruída e a carga retorna erro.
13. Códigos repetidos são verificados antes da montagem, evitando criar listas que não seriam armazenadas.
14. A função `imprimir` passou a mostrar a receita em colunas, com larguras compartilhadas com `imprimirIngrediente` via `std::setw`. As colunas mostram nome, código, perecibilidade, necessidade de preparo e validade em turnos.
15. A função `imprimirIngrediente` mostra `Sim` e `Nao` para os campos booleanos e `-` quando a validade é zero.
16. `contaturnospedido` percorre a lista encadeada da receita e soma o custo dos ingredientes, começando com 1 turno para enviar o pedido.
17. `contaturnospedido` recebe `const ListaEnc *`. As declarações e chamadas foram ajustadas, e a dependência circular entre `listaenc.hpp` e `pedido.hpp` foi removida.

## 6. TAD Hash — encadeamento separado (`hash.hpp` / `hash.cpp`) — mudanças em 06/11, 08/11, 10/11, 14/11

1. A adaptação foi concentrada no encadeamento separado, mantendo as outras implementações com valores inteiros.
2. O campo `valor` de `No` passou de `int` para `const Pedido *`, para guardar referências aos pedidos da AVL.
3. A função `encInserir` passou a receber esse ponteiro, mantendo o código do pedido como chave.
4. A função `encBuscar` passou a devolver `const Pedido *`, ou `nullptr` quando não encontra a chave. A hash não possui nem libera as receitas apontadas.
5. Foi iniciada a preparação das métricas, zerando `hits`, `misses` e `colisoes` em `encInicializar`.
6. Foram adicionados `hits`, `misses` e `colisoes` à `TabelaEnc`, do tipo `unsigned long long`.
7. A função `encBuscar` passou a receber `TabelaEnc` sem `const`, para atualizar os contadores: soma um hit ao encontrar o código ou um miss ao terminar sem encontrá-lo.
8. A função `encInserir` passou a contar uma colisão quando a posição já está ocupada, independentemente do tamanho da lista nessa posição.
9. Foi criada `obterPedido` em `jogo.cpp`, que consulta primeiro a hash; em um miss, busca na AVL e insere a referência encontrada no cache.
10. O cache passou a ser inicializado uma vez no `testemenu`, antes do menu, com tamanho provisório 101.
11. A função `liberarrecursos` ganhou um parâmetro opcional para a hash, liberando o cache antes da AVL. O valor padrão `nullptr` permite usá-la nos erros anteriores à criação do cache.
12. A função `novoJogo` passou a receber o cache criado no `testemenu`, reutilizando a mesma hash entre partidas.
13. A função `sortearPedido` foi movida da AVL para `jogo.cpp` e passou a receber a raiz e o cache.
14. O pedido sorteado agora é recuperado por `obterPedido`: hash primeiro e AVL somente no miss.
15. Foi criada `exibirEstatisticasHash`, mostrando m, n, hits, misses, colisões, fator de carga e taxa de acerto.
16. O fator de carga usa conversão para `double`. A taxa de acerto é calculada em porcentagem com if/else, retornando zero quando não há buscas.
17. As estatísticas passaram a ser exibidas ao final de `novoJogo` e representam os valores acumulados da execução.
18. O comando de compilação do `testemenu` precisa incluir `hash.cpp`.
19. Foi incluído `<iostream>` em `hash.cpp`, pois `exibirEstatisticasHash` usa `std::cout`.
20. `obterPedido` e `sortearPedido` passaram a receber `Metricas met`. No miss da hash, `obterPedido` cronometra `buscarPorCodigo` e acumula `totalBuscas`, `totalComparacoes` e `tempoBuscas`.
21. `exibirEstatisticasHash` passou a copiar m, n, hits, misses e colisoes do cache para a `Metricas`.
22. O Relatório de Desempenho (`geraRelatorio`) inclui fator de carga e taxa de acerto, que valem zero quando o divisor é zero, e é gravado no `medicoes.log`.

**Pendências**
- ✅ Gravar as métricas em `medicoes.log`.
- ❔ Integrar a apresentação das estatísticas ao encerramento real das partidas.
- ⏳ Justificar o tamanho provisório 101.
- ⏳ `zeraMetricasPartida` não é chamada no início de cada partida, e as estatísticas da hash vêm do cache reutilizado entre partidas.

## 7. TAD Heap / Fila de prioridade (`heap.hpp` / `heap.cpp`) — mudanças em 08/11, 09/11, 10/11, 13/11

1. O heap passou de máximo para mínimo: as comparações de `heapify` e `siftUp` foram invertidas, de `>` para `<`. Assim, o topo guarda o menor valor.
2. Na fila de prioridade, a lógica foi mantida, pois ela usa `heapify` e `siftUp`. Em `heap.cpp`, `fpMaximo` passou a se chamar `fpMinimo` e `fpRemoverMaximo` passou a se chamar `fpRemoverMinimo`.
3. Como o min-heap deixa o `heapSort` em ordem decrescente, foi adicionada ao final da função uma inversão do vetor, que devolve a ordem crescente.
4. Cada perecível usa um min-heap próprio (carne, ovo frito e bacon), organizado pelo turno de vencimento, de modo que a unidade mais próxima de vencer fique no topo.
5. Foi criada `calculaTurnoVencimento`, que soma o turno atual à validade do ingrediente.
6. Foi criada `prepararIngredientePerecivel`, que lê o código, insere o vencimento no heap correspondente e retorna false em código inválido, ingrediente de outro tipo ou heap cheio.
7. O `heap.hpp` passou a declarar `fpMinimo` e `fpRemoverMinimo`, acompanhando os nomes usados em `heap.cpp`.
8. O include de `sortings.hpp` foi removido de `heap.cpp`, pois o `heapSort` não chama mais o `mergeSort`.
9. Foi criada `removeIngredienteEstragado`, que retira do min-heap as unidades com turno de vencimento menor ou igual ao turno atual. O laço usa `fpMinimo` e termina quando o heap esvazia ou quando o topo ainda não venceu.
10. Foi criada `usaIngredientePerecivel`, que lê o código e retira do heap correspondente a unidade mais próxima de vencer. Se não houver unidade disponível, avisa o jogador e retorna false.
11. O main de `testeheap.cpp` foi removido, para que suas funções possam ser compiladas junto com o `testemenu`.
12. A função `novoJogo` passou a receber os três heaps de perecíveis (carnes, ovos e bacons), e o `jogo.hpp` passou a incluir `heap.hpp`, onde `FilaPrioridade` é definida.
13. No `testemenu`, cada partida cria e inicializa os três heaps e passa seus endereços para `novoJogo`.
14. A cada turno, `novoJogo` chama `removeEstragadosHeap`, que descarta dos três heaps as unidades vencidas.
15. `usaIngredientePerecivel` passou a receber o código por parâmetro. Depois que o ingrediente entra na pilha, retira-se do heap a unidade com o menor turno de vencimento.
16. A opção Consultar estoque usa `mostrarPerecivel` para exibir, em cada heap não vazio, quanto falta para o próximo vencimento (`turnoVencimento - turnoAtual`). A leitura usa `fpMinimo` e mantém a unidade no heap.

**Pendências**
- ✅ Atualizar as declarações do `heap.hpp` (`fpMinimo` e `fpRemoverMinimo`).
- ✅ Remover o include de `sortings.hpp` em `heap.cpp`.
- ⏳ Atualizar os comentários do `heap.hpp` que ainda descrevem um heap máximo.
- ⏳ Renomear a variável `maior` de `heapify`, que agora guarda o índice do menor elemento.
- ⏳ Corrigir o comentário do `heapSort` que ainda cita o máximo.
- ❔ Incluir os retornos que faltam em `removeIngredienteEstragado` e `usaIngredientePerecivel` (o programa quebrava ao chamar `removeIngredienteEstragado`).
- ✅ Garantir o descarte antes do uso, para que uma unidade vencida não seja consumida (`removeEstragadosHeap` no início de cada turno).

## 8. Ordenação — Merge Sort e Heap Sort (`sortings.hpp` / `sortings.cpp`) — mudanças em 08/11, 09/11, 14/11

1. O Merge Sort foi adaptado para C++.
2. As três funções que compõem o Merge Sort (`merge`, `mergeSortRec` e `mergeSort`) foram adaptadas para receber e ordenar um vetor da struct `Jogador`, porque queremos ordenar o histórico em ordem decrescente para imprimir os 10 melhores escores. (No código atual, as versões adaptadas se chamam `mergeSortRecAdaptado` e `mergeSortAdaptado`.)
3. A função `mergeSort` também registra o tempo de execução e retorna um `double` com esse tempo.
4. Como o min-heap deixa o `heapSort` em ordem decrescente, foi adicionada ao final da função uma inversão do vetor, que devolve a ordem crescente.
5. O include de `sortings.hpp` foi removido de `heap.cpp`, pois o `heapSort` não chama mais o `mergeSort`.
6. Foi criada `medirOrdenacaoHistorico` em `funcoesmenu.cpp`, chamada logo após `iniciaLog`. Ela copia a lista para um vetor fora do intervalo cronometrado, ordena com `mergeSortAdaptado` e guarda tamanho e tempo na `Metricas`.
7. `historicov3` também atualiza `tamanhoOrdenacao` e `tempoOrdenacao` a cada acesso ao Histórico, e o Relatório de Desempenho mostra a ordenação abaixo de "Total de colisoes".

**Pendências**
- ⏳ Medir a ordenação com pelo menos 3 tamanhos de histórico para o relatório.

---

# Parte 2 — Outros módulos

## 9. Ingredientes (`ingredientes.hpp` / `ingredientes.cpp`) — mudanças em 08/11, 15/11

1. Foi criada a struct `Ingrediente`, com nome, símbolo, perecível, requerpreparo e validadeturnos.
2. Os tipos de ingredientes foram definidos como constantes em `ingredientes.hpp`.
3. A função `buscarIngrediente` retorna um ponteiro constante para o ingrediente do símbolo recebido, ou `nullptr` se ele for inválido.
4. A struct `Ingrediente` ganhou o campo `cor`, do tipo `const char *`, e cada constante de ingrediente passou a ter sua cor. Assim, a cor acompanha as cópias guardadas na pilha.
5. O `ingredientes.hpp` passou a incluir `cores.hpp`, e foram criadas as cores `MARROM` e `LARANJA`.
6. `contaturnosingrediente` conta 1 turno para adicionar o ingrediente e mais 1 quando ele exige preparo. Recebe `const Ingrediente *`.

## 10. Leitura e gravação de arquivos — mudanças em 08/11, 10/11, 14/11, 15/11

### Pedidos (carregamento das receitas na AVL)
1. O carregamento monta os pedidos e os insere na AVL antes do menu.
2. A função `montarReceita` converte as letras em nós, inserindo no final para preservar a ordem de montagem.
3. Cada pedido tem sua lista inicializada e preenchida antes da inserção na AVL.
4. Em símbolo inválido ou falha de inserção na lista, a receita parcial é destruída e a carga retorna erro.
5. Códigos repetidos são verificados antes da montagem, evitando criar listas que não seriam armazenadas. O primeiro pedido do código é preservado.
6. A contagem de registros lidos inclui os repetidos e é diferente da quantidade de nós inseridos.
7. Verificação: a carga foi conferida com três pedidos, verificando códigos em ordem crescente, ingredientes na ordem das receitas e abertura do menu.
8. O sorteio de pedidos passou a usar o menor e o maior código da árvore, sem reler o arquivo.
9. O carregamento passa `met.rotacoes` para `avlInserir`, e a `Metricas` guarda os dados do carregamento da AVL e do histórico.

### Histórico
10. Foi criada `gravaJogoNoHistorico`, que acrescenta o nome e o score ao final do arquivo, no mesmo formato do `historico.txt` (nome em uma linha, score na seguinte). O nome é lido com `getline(cin >> ws, nome)`, para aceitar nomes com espaço, e o score começa em zero.
11. Na leitura do histórico, o `'\r'` passou a ser removido do nome antes de copiá-lo para o `Jogador`. Antes, a remoção acontecia depois da cópia, e o nome guardado continuava com o `'\r'`.
12. `gravaJogoNoHistorico` passou a receber a `listahistorico` e, além de gravar no arquivo, insere o novo `Jogador` no fim da lista. `novoJogo` recebe a lista do `testemenu` e a repassa.
13. `gravaJogoNoHistorico` passou a receber `const char *nomeArqHistorico` e abre esse arquivo com `std::ios::app`, em vez do caminho fixo `"src/historico.txt"`.
14. `novoJogo`, que já recebia `argv`, passa `argv[2]` para `gravaJogoNoHistorico`. Assim, o jogo grava no mesmo arquivo de histórico que foi lido na inicialização. A assinatura de `novoJogo` não mudou.

### `medicoes.log`
15. `iniciaLog` abre o `medicoes.log` sem `std::ios::app`, recriando o arquivo a cada execução. As demais gravações usam `std::ios::app`.

**Pendências**
- ✅ `gravaJogoNoHistorico` gravava em arquivo fixo (`historicoteste.txt` e, depois, `"src/historico.txt"`), e não no arquivo recebido em `argv[2]`.
- ✅ `gravaJogoNoHistorico` não era chamada (passou a ser chamada a partir de `novoJogo`). ❔ A declaração em `jogo.hpp` não foi registrada.
- ⏳ `gravaJogoNoHistorico` não valida o score.
- ⏳ `"medicoes.log"` continua com nome fixo no `testemenu.cpp` e no `jogo.cpp`.

## 11. Medições e `medicoes.log` (`medicoes.hpp` / `medicoes.cpp`) — mudanças em 14/11

1. Foi criado o módulo `medicoes.hpp/.cpp`, com a struct `Metricas` (carregamento da AVL e do histórico, buscas na AVL, hash e ordenação) e as funções `iniciaLog`, `geraRelatorio`, `registraOrdenacao` e `zeraMetricasPartida`. O `medicoes.hpp` tem include guard e declara `extern Metricas met`, definida no `testemenu.cpp`.
2. `iniciaLog` abre o `medicoes.log` sem `std::ios::app`, recriando o arquivo a cada execução. As demais gravações usam `std::ios::app`.
3. `geraRelatorio` monta o Relatório de Desempenho uma vez e envia o mesmo texto para a tela e para o log, ao final de `novoJogo`. Média de comparações, fator de carga e taxa de acerto valem zero quando o divisor é zero.
4. AVL: `reequilibrar` e `avlInserir` contam as rotações da inserção (1 nas simples, 2 nas duplas); `buscarPorCodigo` conta as comparações; a altura registrada é `avlAltura(raiz) + 1`.
5. Hash: no miss, `obterPedido` cronometra `buscarPorCodigo` e acumula `totalBuscas`, `totalComparacoes` e `tempoBuscas`; `exibirEstatisticasHash` copia m, n, hits, misses e colisoes para a `Metricas`.
6. Ordenação: `medirOrdenacaoHistorico`, chamada logo após `iniciaLog`, copia a lista para um vetor fora do intervalo cronometrado, ordena com `mergeSortAdaptado` e guarda tamanho e tempo na `Metricas`.
7. `historicov3` também atualiza `tamanhoOrdenacao` e `tempoOrdenacao` a cada acesso ao Histórico, e o Relatório de Desempenho mostra a ordenação abaixo de "Total de colisoes".
8. O comando de compilação passou a incluir `src/medicoes.cpp`.

**Pendências**
- ✅ Gravar as métricas da hash em `medicoes.log`.
- ⏳ `zeraMetricasPartida` não é chamada no início de cada partida, e as estatísticas da hash vêm do cache reutilizado entre partidas.
- ⏳ Medir a ordenação com pelo menos 3 tamanhos de histórico.
- ⏳ `"medicoes.log"` continua com nome fixo no `testemenu.cpp` e no `jogo.cpp`.
- ⏳ O `medicoes.cpp` tem um main de rascunho, que gera "multiple definition of main" se for compilado junto com o `testemenu.cpp`.

## 12. Partida (`novoJogo`), turnos e paciência (`jogo.hpp` / `jogo.cpp`) — mudanças em 04/11, 06/11, 08/11, 10/11, 13/11, 14/11, 15/11

1. A função `novoJogo` passou a preparar uma fila própria por partida, com três clientes e paciência provisória sorteada entre 9 e 15, igual para todos na mesma partida.
2. O cliente da frente é consultado e recebe um pedido sorteado da AVL, exibindo identificador, paciência, código e receita.
3. A fila é liberada ao retornar da função, inclusive em falhas de criação ou obtenção do pedido.
4. A raiz da AVL e `argv` são passados à função `novoJogo` pela opção Novo jogo do menu.
5. Cada cliente passou a receber um sorteio próprio de paciência entre 9 e 15; os valores podem se repetir.
6. O pedido é sorteado e associado ao cliente antes de ele ser enfileirado, e o enfileiramento é feito em `novoJogo`, verificando o retorno de `enfileira`.
7. O atendimento consulta o pedido pelo campo `pedidocliente` do cliente da frente, em vez de manter apenas uma variável separada.
8. A fila parcial é liberada se a obtenção do pedido ou o enfileiramento falhar.
9. A função `novoJogo` passou a receber o cache criado no `testemenu`, reutilizando a mesma hash entre partidas. As estatísticas da hash passaram a ser exibidas ao final de `novoJogo`.
10. A função `novoJogo` passou a receber a pilha do hambúrguer (`PilhaEnc *`), os três heaps de perecíveis (carnes, ovos e bacons), o turno atual e o vetor com as quantidades dos não perecíveis preparados. O `jogo.hpp` passou a incluir `heap.hpp` e `pilha.hpp`, e a declaração de `novoJogo` foi atualizada.
11. No `testemenu`, cada partida cria e inicializa a pilha, os três heaps e o vetor de quantidades (zerado), e passa seus endereços para `novoJogo`.
12. A cada turno, `novoJogo` chama `removeEstragadosHeap`, que descarta dos três heaps as unidades vencidas. Em seguida, o jogador escolhe entre adicionar ou remover ingrediente do hambúrguer, enviar o pedido, preparar perecível ou preparar não perecível.
13. A opção Consultar estoque compensa o avanço do turno e o desconto de paciência feitos pelo laço, para voltar ao menu no mesmo turno.
14. `novoJogo` recebe a `listahistorico` do `testemenu` e a repassa para `gravaJogoNoHistorico`. Ao final, `geraRelatorio` mostra e grava o Relatório de Desempenho.
15. `novoJogo` passa `argv[2]` para `gravaJogoNoHistorico`. A assinatura de `novoJogo` não mudou.
16. `contaturnosingrediente` conta 1 turno para adicionar o ingrediente e mais 1 quando ele exige preparo.
17. `contaturnospedido` percorre a lista encadeada da receita e soma o custo dos ingredientes, começando com 1 turno para enviar o pedido.
18. Em `novoJogo`, a paciência inicial de cada cliente passou a ser o custo do seu pedido mais 2 turnos de margem.
19. `novoJogo` chama `desenharhamburguer` na tela da partida.

**Pendências**
- ❔ Implementar o atendimento, o desconto de paciência e a retirada dos clientes atendidos (o desconto de paciência já aparece em um registro posterior).
- ⏳ `turnoAtual` é recebido por valor em `novoJogo`.

## 13. Estoque e preparo de ingredientes (`testeheap.cpp` na época do registro) — mudanças em 08/11, 09/11, 10/11, 13/11

1. Cada perecível usa um min-heap próprio (carne, ovo frito e bacon), organizado pelo turno de vencimento, de modo que a unidade mais próxima de vencer fique no topo.
2. Foi criada `calculaTurnoVencimento`, que soma o turno atual à validade do ingrediente.
3. Foi criada `prepararIngredientePerecivel`, que lê o código, insere o vencimento no heap correspondente e retorna false em código inválido, ingrediente de outro tipo ou heap cheio.
4. Foi criada `prepararIngredientePerene`, que lê o código e soma uma unidade no vetor de contadores, cujas posições 0 a 3 são queijo suíço, queijo cheddar, cebola e tomate. Retorna false em código inválido e para ingredientes perecíveis ou que não precisam de preparo.
5. Foi criada `removeIngredienteEstragado`, que retira do min-heap as unidades com turno de vencimento menor ou igual ao turno atual. O laço usa `fpMinimo` e termina quando o heap esvazia ou quando o topo ainda não venceu.
6. Foi criada `usaIngredientePerecivel`, que lê o código e retira do heap correspondente a unidade mais próxima de vencer. Se não houver unidade disponível, avisa o jogador e retorna false.
7. Foi criada `usaIngredientePerene`, que lê o código e retira uma unidade do vetor de contadores. Retorna false em código inválido, sem unidade disponível ou para ingredientes que não precisam de preparo.
8. `novoJogo` passou a receber os três heaps, o turno atual e o vetor de quantidades dos não perecíveis preparados; o `testemenu` cria esse vetor zerado a cada partida.
9. A cada turno, `removeEstragadosHeap` descarta dos três heaps as unidades vencidas, e o jogador pode preparar perecível ou não perecível.
10. A opção de adicionar ingrediente passou a ler o código uma vez e encaminhá-lo a `usaIngredientePerecivel` ou `usaIngredienteNaoPerecivel`. As duas funções agora recebem o código por parâmetro.
11. O estoque é baixado depois que o ingrediente entra na pilha. Para perecíveis, retira-se do heap a unidade com o menor turno de vencimento. Para não perecíveis que exigem preparo, reduz-se o contador correspondente. Ingredientes ilimitados são adicionados diretamente.
12. A opção Consultar estoque usa `mostrarEstoque` e `mostrarPerecivel` para exibir quantidades e, em cada heap não vazio, quanto falta para o próximo vencimento (`turnoVencimento - turnoAtual`). A leitura usa `fpMinimo` e mantém a unidade no heap.
13. A consulta compensa o avanço do turno e o desconto de paciência feitos pelo laço, para voltar ao menu no mesmo turno.

**Pendências**
- ❔ Ler o código uma única vez e decidir qual função de preparo chamar (feito para o uso; para o preparo, não registrado).
- ❔ Gastar o turno apenas quando o preparo der certo (as funções já foram levadas ao jogo).
- ✅ Dar baixa no estoque ao usar o ingrediente.
- ✅ Descartar os perecíveis vencidos no início de cada turno.
- ❔ Testar as funções e escrever os testes (o main de `testeheap.cpp` estava vazio e foi removido).
- ❔ Incluir os retornos que faltam em `removeIngredienteEstragado` e `usaIngredientePerecivel` (o programa quebrava ao chamar `removeIngredienteEstragado`).
- ✅ Garantir o descarte antes do uso, para que uma unidade vencida não seja consumida.
- ✅ Tratar à parte os ingredientes sem preparo, que têm quantidade infinita.
- ✅ Integrar as funções à pilha do hambúrguer e ao jogo.
- ✅ A opção 1 do turno chamava `adicionaringrediente` diretamente, sem consumir o estoque dos heaps e do vetor de quantidades.

## 14. Organização dos módulos e compilação — mudanças em 08/11, 10/11, 14/11, 15/11

1. O antigo módulo lista foi separado em `listacontest.hpp/.cpp`, para o histórico, e `listaenc.hpp/.cpp`, para as receitas.
2. Os includes e o comando de compilação foram atualizados para os novos arquivos, incluindo `ingredientes.cpp`.
3. A struct `Pedido` foi movida para `pedido.hpp`.
4. O comando de compilação do `testemenu` precisa incluir `hash.cpp`.
5. A compilação do teste da pilha precisa de `listaenc.cpp`.
6. O main de `testeheap.cpp` foi removido, e o main de `testepilha.cpp` ficou entre `#ifdef TESTEPILHAMAIN` e `#endif`. Assim, as funções dos dois arquivos podem ser compiladas junto com o `testemenu`, que tem o único main do jogo. Para testar a pilha sozinha, compila-se com `-DTESTEPILHAMAIN`.
7. O comando de compilação do jogo passou a incluir `heap.cpp`, `testeheap.cpp`, `testepilha.cpp` e `pilha.cpp`.
8. O `jogo.hpp` passou a incluir `heap.hpp` e `pilha.hpp`, onde são definidos `FilaPrioridade` e `PilhaEnc`.
9. O `jogo.hpp` ganhou a declaração antecipada `struct ListaContEst;`, pois o `listacontest.hpp` inclui o `jogo.hpp` e incluir o contrário formaria um ciclo.
10. O `medicoes.hpp` tem include guard e declara `extern Metricas met`, definida no `testemenu.cpp`.
11. O comando de compilação passou a incluir `src/medicoes.cpp`.
12. A definição de `Jogador` foi movida de `listacontest.hpp` para `jogo.hpp`.
13. A dependência circular entre `listaenc.hpp` e `pedido.hpp` foi removida.

**Pendências**
- ⏳ Atualizar o comando de compilação no comentário do `testemenu.cpp`.
- ⏳ O `medicoes.cpp` tem um main de rascunho, que gera "multiple definition of main" se for compilado junto com o `testemenu.cpp`.
- ⏳ O `src/main.cpp` está vazio.

---

## 15. Pendências em aberto (resumo)

Itens ⏳ e ❔ das seções acima, segundo este registro:

- **Fila / Partida:** ❔ atendimento e retirada dos clientes atendidos; ⏳ `turnoAtual` recebido por valor em `novoJogo`.
- **Pilha:** ❔ adaptar `desempilha` e `topo` (antigo `Produto`); ⏳ "Pao de baixo" duplicado em `imprimirhamburguer`; ⏳ chamar `esvaziarPilha` depois de cada partida.
- **Hash:** ❔ apresentação no encerramento real das partidas; ⏳ justificar o tamanho 101; ⏳ `zeraMetricasPartida` não chamada (cache reutilizado entre partidas).
- **Heap:** ⏳ comentários do `heap.hpp` (heap máximo); ⏳ variável `maior` em `heapify`; ⏳ comentário do `heapSort`; ❔ retornos faltando em `removeIngredienteEstragado` e `usaIngredientePerecivel`.
- **Ordenação:** ⏳ medir com pelo menos 3 tamanhos de histórico.
- **Estoque e preparo:** ❔ ler o código uma vez no preparo; ❔ gastar o turno só quando o preparo der certo; ❔ testes.
- **Arquivos e medições:** ⏳ `gravaJogoNoHistorico` não valida o score; ❔ declaração de `gravaJogoNoHistorico` em `jogo.hpp`; ⏳ `"medicoes.log"` com nome fixo; ⏳ main de rascunho em `medicoes.cpp`.
- **Compilação:** ⏳ comando no comentário do `testemenu.cpp`; ⏳ `src/main.cpp` vazio.
