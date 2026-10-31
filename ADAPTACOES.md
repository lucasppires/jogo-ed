# Adaptações realizadas nas estruturas que nos foram dadas

Primeiramente, transformaram-se os códigos do moodle em C para C++ (.c para .cpp). Em seguida, adaptou-se o conteúdo do código, pq apesar de C ser um subconjunto de C++, é necessário adaptar alguns pontos do código. Por exemplo, malloc (em C) e new (em C++).

Adaptações no TAD AVL:

1. O struct NodoAvl agora possui o campo receita, do tipo string.
2. A função AvlInserir agora recebe como parâmetro o string receita.
3. A função criarNodo agora recebe como parâmetro o string receita.

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

