// Study case of W. W. Zachary's Karate Club (1977)
// For UnB - Theory and Application of Graphs, 2018/1
// by Giovanni M Guidini 16/0122660 and Vitor F Dullens  16/0148260

// This program explores graph representations and cliques in a graph in the following steps:
// 1. The graph is generated from a .gml graph using gmlParser.h, by Thiago Veras (modified)
// 2. A list of nodes is presented, ordered by the decreasing number of connections.
// 3. A view of the graph is generated using svg.h, by us
// 4. K-cliques (with k >= 4) are found using Bron-Kerbosch's algorithm with pivoting
// 5. 2 cliques are presented, being the maximum and a maximal

// test compiled in 4.14.30-1-MANJARO using g++ (GCC) 7.3.1 20180312
#include <bits/stdc++.h>
#include "gmlParser.h"
#include "svg.h"

using namespace std;

// mostra a estrutura do grafo no terminal -- debugging
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

// ordenar nodes por maior numero de conexoes
bool cmp(const pair<int, int>&i, const pair<int, int>&j){
    if(i.second == j.second){
        return i.first < j.first;
    }

    return i.second > j.second;
}

// lista nodes e numero de conexoes em ordem decrescente
vector<pair<int,int>> listSorted(vector<int>* G){
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

    return arr;
}


vector<int> intersection(vector<int> A, vector<int> B){
    // necessary to use intersection
    vector<int> R;
    sort(A.begin(), A.end());
    sort(B.begin(), B.end());
    set_intersection(A.begin(), A.end(), B.begin(), B.end(), back_inserter(R));
    return R;
}

vector<int> difference(vector<int> A, vector<int> B){
    vector<int> R;
    sort(A.begin(), A.end());
    sort(B.begin(), B.end());
    set_difference(A.begin(), A.end(), B.begin(), B.end(), back_inserter(R));
    return R;
}

void eraseByValue(vector<int>& A, int el){
    for(int i = 0; i < (int) A.size(); i++){
        if(A[i] == el){
            A.erase(A.begin()+i);
            return;
        }
    }
}
// global vector to store all the cliques
vector<vector<int>> cliques;
// encontra cliques maximais
void BronKer(vector<int> R, vector<int> P, vector<int> X){
    // the original graph for reference
    vector<int>* G = getGraph();

    // if it's a maximal clique, report
    if(P.empty() && X.empty()){
        // filter for k-cliques with k >= 4
        if(R.size() >= 4){
            cliques.push_back(R);
        }
        return;
    }
    else if(P.empty()){
        // no more nodes, but not a clique
        return;
    }

    // keeping track of active nodes
    vector<int> K;
    
    // pivot element.
    int u = P.front();
    K = difference(P, G[u]);

    // iterate through all possibilities
    // NOT GETTING THE RIGHT ONES
    for(auto v : K){
            R.push_back(v);

            // recursive call
            BronKer(R, intersection(P, G[v]), intersection(X, G[v]));

            R.pop_back(); // removes v
            eraseByValue(P, v);
            X.push_back(v);

    }
}

bool sortCliques(const vector<int> A, const vector<int> B){
    return A.size() > B.size();
}

void join(vector<int> A, char delim = ','){
    printf("{%d", A[0]);
    int n = A.size();
    for(int i = 1; i < n; i++){
        printf("%c %d", delim, A[i]);
    }
    printf("}\n");
}

// show remaining cliques
void showAllCliques(){
    int k = cliques.size();
    for(int i = 2; i < k; i++){
        printf("Clique maximal\n");
        join(cliques[i]);
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
    
    // sorts nodes by connections
    vector<pair<int, int>> sorted_G = listSorted(G);

    // generates view of graph
    printGraph(G);

    // how we're only interested in k-cliques with k >= 4
    // all nodes with less than 4 connections are irrelevant
    vector<int> bigG, a, b;
    for(auto e : sorted_G){
        if(e.second >= 4){
            bigG.push_back(e.first);
        }
    }

    // finds cliques
    BronKer(a, bigG, b);
    
    // sort cliques
    sort(cliques.begin(), cliques.end(), sortCliques);

    // show two bigger cliques
    printf("Clique máximo\n");
    join(cliques[0], ',');
    printf("Clique maximal\n");
    join(cliques[1], ',');
    
    // Uncomment to list all k-cliques with k >= 4
    //showAllCliques();
}