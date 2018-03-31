Project 1 was created by Vitor F Dullens and Giovanni M Guidini for our Theory and Application of Graphs discipline at UnB (2018/1).

Special thanks for Thiago Veras Machado for letting us use his gmlParser.h, which was slightly modified by us.

# To do
- [X] O projeto consiste em escrever um programa em C/C++ que lê o arquivo (karate.gml), monta com esses dados um grafo não direcionado, sem pesos, usando listas de adjacências, e imprime como saída (tela) em ordem decrescente, os integrantes (vértices) com maiores graus no grafo, até o de menor. Essa impressão deve ser somente pelos integrantes, e consequentes graus desses vértices. Uma visualização em gráfico, mostrando o grafo montado é um ponto adicional (i.e. 11, caso alguém queira fazer). Além disso, o programa deve encontrar e imprimir um (1) clique maximal (com no mínimo 5 alunos), e um (1) clique máximo desse grafo, ambos diferentes.

# Usage
    1. Download Project 1
    2. Compile karate.cpp (we recommend using g++ -std=c++11 -o k)
    3. Execute informing .gml file name (i.e. ./k karate.gml)
    
# Notes
The file "k" is a compiled version of the program. Should work on linux systems.

File "out_34.html" is a view of the graph.

More cliques are found by the program, but only the 2 bigger ones are shown. To show all cliques
uncomment showAllCliques() function and recompile.
