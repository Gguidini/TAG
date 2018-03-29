#include <bits/stdc++.h>
#include "gmlParser.h"

using namespace std;

void showGraph(vector<int>* G){
    int l = graphSize();
    printf("O grafo contém %d nodes\n", l);

    for(int i = 1; i <= l; i++){
        cout << getID(i) << "\tConnects with: ";
        for(auto e: G[i]){
            printf("-> %*s ", 2, getID(e).c_str());
        }
        printf("\n");
    }
}

bool cmp(const pair<int, int>&i, const pair<int, int>&j){
    if(i.second == j.second){
        return i.first < j.first;
    }

    return i.second > j.second;
}

void listSorted(vector<int>* G){
    int l = graphSize();
    // vetor para o indice e numero de conexoes
    vector<pair<int,int>> arr(l);

    for(int i = 1; i <= l; i++){
        arr[i-1] = make_pair(i, G[i].size());
    }

    // sorting array by nunber of connections
    sort(arr.begin(), arr.end(), cmp);

    printf("\n\nNodes em ordem DECRESCENTE de conexoes\n");
    printf("Node\tNumero de Conexoes\n");
    for(int i = 0; i < l; i++){
        cout << getID(arr[i].first) << "\t" << arr[i].second << endl;
    }
}

int main(int argc, char* argv[]){
    // limpa estruturas do grafo na lib
    initGraph();
	// Variavel para ler o nome do arquivo que contem o grafo
	string file;
    if(argc == 2){
        file = string(argv[1]);
    }
    else{
        cout << "Input gml file name: ";
	    // Le o nome do arquivo
	    cin >> file;
    }

	//Tenta ler o arquivo e caso nao exista, encerra o programa
	if (!read(file + ".gml")){
		cout << "System finished" << endl;
		return 0;
	}

    // referencia para o grafo da lib
    vector<int>* G = getGraph();
    showGraph(G);
    listSorted(G);
}