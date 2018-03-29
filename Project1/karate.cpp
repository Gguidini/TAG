#include <bits/stdc++.h>
#include "gmlParser.h"

using namespace std;

void showGraph(vector<int>* G){
    int l = graphSize();
    printf("O grafo contém %d nodes\n", l);

    for(int i = 1; i <= l; i++){
        cout << getID(i) << "\tConnects with: ";
        for(auto e: G[i]){
            cout << "-> " << getID(e) << " ";
        }
        printf("\n");
    }
}

int main(){
    // limpa estruturas do grafo na lib
    initGraph();
	// Variavel para ler o nome do arquivo que contem o grafo
	string file;
	cout << "Input gml file name: ";
	// Le o nome do arquivo
	cin >> file;
	//Tenta ler o arquivo e caso nao exista, encerra o programa
	if (!read(file + ".gml")){
		cout << "System finished" << endl;
		return 0;
	}

    // referencia para o grafo da lib
    vector<int>* G = getGraph();
    showGraph(G);
}