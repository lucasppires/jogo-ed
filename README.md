# jogo-ed
Trabalho final da disciplina de Estrutura de Dados. Lucas Pires e Mateus Schenato

Primeiro tempo da leitura dos pedidos na AVL: 1.25036 segundos (837253 pedidos).

Primeira leitura do historico: 100000 partidas lidas em 0.0272331 s
## Compilar e executar

O ponto de entrada oficial é `src/main.cpp`. Na raiz do projeto, compile com:

~~~sh
g++ src/main.cpp src/funcoes_menu.cpp src/jogo.cpp src/fila.cpp src/leitura_de_arquivos.cpp src/listacontest.cpp src/listaenc.cpp src/ingredientes.cpp src/avl.cpp src/hash.cpp src/timer.cpp src/sortings.cpp src/heap.cpp src/pilha.cpp src/hamburguer.cpp src/preparo.cpp src/medicoes.cpp -I src -o dado_burger.exe -Wall -std=c++17
~~~

No PowerShell, execute:

~~~powershell
.\dado_burger.exe data\pedidos.txt data\historico.txt
~~~

No Bash, execute:

~~~bash
./dado_burger.exe data/pedidos.txt data/historico.txt
~~~

Os dois argumentos indicam os arquivos de pedidos e histórico. Para a apresentação, passe os caminhos dos arquivos finais nesses argumentos. Execute a partir da raiz do projeto, que contém a pasta `data`, onde o programa grava `medicoes.log`.
