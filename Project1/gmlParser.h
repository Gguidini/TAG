// Por Thiago Veras Machado
// Modificada por Giovanni Guidini e Vitor Dullens onde especificado
#include <bits/stdc++.h>

using namespace std;

vector<int> grafo[1000];
map<int,string> node;
map<string,int> nodes;

bool read(string file){
	// Variável para gerar os indices de cada vértice
	int idx = 1; 
	// Ler as linhas do arquivo e os dados para criar o grafo;
	string line, source, target;  
	fstream arquivo;
	// Abre o arquivo
	arquivo.open(file); 
	if(!arquivo){
		cout << "Falha ao abrir o arquivo" << endl;
		// Retorna falso caso nao tenha conseguido abrir o arquivo
		return false; 
	}
	//Percorre o arquivo
	while(arquivo >> line){ 
		// Quando chega em um nó
		if(line == "node"){ 
			//Vai pulando todos os dados até chegar no id
			while(arquivo >> line, line != "id"); 
			//Le o id
			arquivo >> line; 
			//Gera o numero para aquele id, que pode ser um nome, um numero, um simbolo ...
			node[idx] = line;
			// Gera o contrário para conseguir pegar acessar os dados do no depois
			nodes[line] = idx++; 
		}
		else if(line == "edge"){ //Quando chega em uma aresta
			//Pula todos os caracteres até chegar no source
			while(arquivo >> line, line != "source"); 
			//Le o source
			arquivo >> source;
			//Pula todos os caracteres até chegar no target
			while(arquivo >> line, line != "target");
			// Le o target
			arquivo >> target;
			//Insere no grafo não direcional 
			grafo[nodes[source]].push_back(nodes[target]); 
			grafo[nodes[target]].push_back(nodes[source]);
		}
	}
	// Retorna true caso tudo tenha ocorrido corretamente
	return true; 
}

// Modificações para permitir a utilização das estruturas do grafo 
// No programa principal

// limpa estruturas do grafo
void initGraph(){
    for(int i = 0; i < 1000; i++){
        grafo[i].clear();
    }
    node.clear();
    nodes.clear();

}

// retorna o grafo
vector<int>* getGraph(){
    return grafo;
}

// retorna o indice de um no no grafo
int getIdx(string n){
    return nodes[n];
}

// retorna o ID de um no a partir do seu indice no grafo
string getID(int idx){
    return node[idx];
}

// retorna a quantidade de nos no grafo
int graphSize(){
    return node.size();
}