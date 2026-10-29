# Adaptações realizadas nas estruturas que nos foram dadas

Primeiramente, transformaram-se os códigos do moodle em C para C++ (.c para .cpp). Em seguida, adaptou-se o conteúdo do código, pq apesar de C ser um subconjunto de C++, é necessário adaptar alguns pontos do código. Por exemplo, malloc (em C) e new (em C++).

Adaptações no TAD AVL:

1. O struct NodoAvl agora possui o campo receita, do tipo string.
2. A função AvlInserir agora recebe como parâmetro o string receita.
3. A função criarNodo agora recebe como parâmetro o string receita.
4. 

