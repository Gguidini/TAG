# Resumo da Prova 2 de Teoria e Aplicação de Grafos

## Arvores geradoras minimas

**Objetivo:** encontrar o conjunto de arestas de menor custo que conecte todos os vertices de um grafo.

**Requisitos:** grafo não direcionado, conexo e ponderado.

**Algoritmos:** [Prim](https://www.ime.usp.br/~pf/algoritmos_para_grafos/aulas/prim.html) ou [Kruskal](https://www.ime.usp.br/~pf/algoritmos_para_grafos/aulas/kruskal.html).

**Custo:** O(n²) - pode haver variações.
### exemplo
![exemplo](http://danielamaral.wikidot.com/local--files/agmmo/GrafoPesosAGM.png)
Em verde a árvore gerado minima.

## Cortes e Blocos

### Cortes
Remoção de um vertice V que gera 2 ou mais grafos conexos. Porém o grafo incial G não é mais conexo.

**exemplo**


![exemplo](https://i.stack.imgur.com/A8gyC.png)

### Blocos 
Um grafo conexo onde não é possível fazer cortes. 

Como é possivel ver na imagem acima, se o vertice em vermelho for retirado, não existe mais vertice de Corte, com isso é um Bloco.

## Grafos Bipartidos

É um tipo de grafo onde é possivel dividir os vértices em dois conjuntos distindos, ou seja, que não possuem arestas que ligam elementos do mesmo conjunto.

**Algortimo:** utilizando um DFS ou uma BFS é possível passar colorindo o grafo com 2 cores diferentes. Quando dois vertices adjacentes tem a mesma cor o grafo não é bipartido.

**Requisitos:** grafos bipartidos não possuem [ciclos impares](https://www.ime.usp.br/~pf/algoritmos_para_grafos/aulas/bipartite.html).

### Código para identificar se um grafo é bipartido ou não

```C++
bool bipartite(int u){
    int ans = 1;
    for(auto v : grafo[u]){
        if(color[v] == -1){
            color[v] = !color[u];
            ans &= bipartite(v);
        }
        else
            ans &= !(color[v] == color[u]);
    }
    return ans;
}
```

**exemplo**

![exemplo](https://www.researchgate.net/profile/Esly_Junior/publication/319276416/figure/fig8/AS:531223680634887@1503665003756/Figura-3-4-Grafo-bipartido-inicial-para-o-problema-do-pendulo-utilizado-no-algoritmo.png)

## Emparelhamento e Cobertura

### Cobertura

Conjunto de vertices que cobrem(incluem) todas as arestas.

**Cobertura Minima:** é a menor cobertura possível.

### Emparelhamento

Conjunto de arestas que não compartilham nenhum vertice terminal.

**exemplo**

![exemplo](http://www.professeurs.polymtl.ca/michel.gagnon/Disciplinas/Bac/Grafos/Map/map_aum3.gif)
Em negrito é um exemplo de emparelhamento.

**Emparelhamento Perfeito:** é um emparelhamento que satura todos os vertices do grafo.

**Emparelhamento Maximo:** um emparelhamento que satura o maior número possivel de vertices num grafo.
```
1 começar com um emparelhamento qualquer
2 se M satura todos os vertices de X, fim!
3 se nao:
    i   escolher u em X não-saturado
    ii  procurar um caminho M-aumentado com origem em u
    iii se achou, inverter arestas formando emparelhamento em u', voltar ao passo 2
    iv  se não, fim!
```

**Emparelhamento Maximal:** um emparelhamento que não pode ser expandido, mas não é necessariamente o maior emparelhamento.
![](maximalVSmaximo.png)
**Emparelhamento Estavel:** em um grafo que cada um dos conjuntos possuem prioridades, o emparelhamento estável é aquele que melhor escolhe as combinações. Podendo ser ótimo pra um conjunto ou para o outro.
``` 
Algoritmo de Gale-Shapley
1 inicializa cada pessoa como livre
    
```

### observação

`n° de arestas do Emparelhamento Maximo == n° de vertices da Cobertura Minima`

## Algoritmo Húngaro

**Objetivo:** Minimizar o custo atravéz de operações de soma e subtração de uma matriz.

**exemplo:** [video aula](https://www.youtube.com/watch?v=sZQwhs_uDCs)

**Algoritmo**
```
Matriz(n x n)
1 de cada linha, subtrair o menor elemento
2 de cada coluna, subtrair o menor elemento
3 encontrar conjunto maximo de N' zeros independentes (nao compartilham a mesma linha nem coluna)
4 se N'= n retornar índices dos zeros
5 se não:
    i   cobrir todos os zeros com N' linhas ou colunas
    ii  encontrar valor mínimo não coberto (k)
    iii subrair k dos elementos não cobertos
    iv  somarar k dos elementos duplamente cobertos
    v   voltar para o passo 3
```

### notas
Por favor, complementem com o que acharem necessário :+1:
