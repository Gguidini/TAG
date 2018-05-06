// Created by Vitor F Dullens 
// and Giovanni M Guidini 16/0122660
#include <bits/stdc++.h>
#include "gnuplot-cpp/gnuplot_i.hpp"

using namespace std;

// graph
vector<int> G[1000000];
// lista de incidencia
vector<int> IN(1000000);
// pilha com resutados dfsSort
stack<int> P;
// tamanho do grafo
int size;

// making it working in bloddy windows
#ifdef __WIN32
    #define SLASH "\\"
#else
    #define SLASH "/"
#endif

void readGraph(string file){
    ifstream fd (file);
    if(fd){
        int n;
        fd >> n;
        size = n;   // size of graph
        int d, t;
        while(fd >> d >> t){
            // cria lista de incidencia
            IN[t]++;
            // cria aresta no grafo
            G[d].push_back(t);
        }
    }
    else{
        printf("File not found\n");
    }
}

// topological sort using Kahn's algorithm
string kahnSort(){
    queue<int> Q;
    string out = "";
    // initial nodes
    for(int i = 0; i < size; i++){
        if(IN[i] == 0){
            Q.push(i);
        }
    }
    // main loop
    while(!Q.empty()){
        int el = Q.front(); Q.pop();
        // add to sequence
        out += to_string(el) + ",";

        // passeia pelas adjacencias de el
        for(auto v : G[el]){
            IN[v]--;    // diminui em 1
            if(IN[v] == 0){
                Q.push(v);
            }
        }
    }
    return out.substr(0, out.size()-1); // pop back remove a última vírgula
}

void dfs(int pos, bool *visited){
    visited[pos] = true;
     //cout << "aqui2" << endl;

    for (auto v : G[pos]) // percorre todos os filhos, se nao visitados chama a função novamente
        if(!visited[v])
            dfs(v, visited);
    
    P.push(pos); // empilha os nós
}

// topological sort using a dfs
string dfsSort(){
    bool visited[size]; // checar nós visitados
    memset(visited, false , sizeof(visited)); // setar valor inicial como 0
    for(int i = 0; i < size; i++)
        if (!visited[i]) 
            dfs(i, visited);
    

    string result;
    int resp;
    while (!P.empty()){
        resp = P.top();
        result += to_string(resp) + ",";
        P.pop();
    }
    return result.substr(0, result.size() - 1);
    
}

void gnuPlot() {
    
}

// TODO: Dullens, add sua matricula, por favor.
void header(){
    printf("################################################\n");
    printf("#       Projeto 2 - TAG - Unb - 2018/1         #\n");
    printf("################################################\n");
    printf("#      Aluno: Vitor F Dullens - 16/???????     #\n");
    printf("#   Aluno: Giovanni M Guidini - 16/0122660     #\n");
    printf("################################################\n");
    printf("#               Algorithms Used                #\n");
    printf("# 1) Kahn's Algorithm                          #\n");
    printf("# Create topological sort from incoming edges  #\n");
    printf("# of nodes. O(V+E) + time to create list of    #\n");
    printf("# incoming edges (done when reading).          #\n");
    printf("#                                              #\n");
    printf("# 2) Topological Sort with DFS                 #\n");
    printf("# Modified DFS to generate topological sort by #\n");
    printf("# adding finished nodes in a stack. The stack, #\n");
    printf("# at the end of execution, is a valid          #\n");
    printf("# topological sort. O(V+E).                    #\n");
    printf("################################################\n");
}

int main(){
    header();
    // save execution times
    ofstream data;
    data.open("data.txt", ios::trunc);
    vector<double> timesIncidenceSort(4);
    vector<double> timesDFSSort(4);
    // the 4 graphs
    vector<string> files = {"top_small.txt", "top_med.txt", "top_large.txt", "top_huge.txt"};
    // execute main loop for all graphs
    for (auto f : files){
        cout << "Processando arquivo " << f << endl;
        string path = "top_datasets" + (SLASH + f);
        // reads graph + creates incidency list
        readGraph(path);
        data << size << endl;
        clock_t t0 = clock();
        // first sorting algorithm
        string order = kahnSort();
        clock_t t1 = clock();
        timesIncidenceSort.push_back((double) (t1-t0)); // saves time
        cout << "+----------- TOPOLOGICAL SORT USING INCIDENCY LIST -----------" << endl;
        // cout << "SORTED ORDER - " << f << " - kahnSort ALGORITHM\n" << order << endl;
        cout << "CLOCK CICLES - " << (int) (t1-t0) << endl;
        cout << "TIME - " << (double) (t1-t0)/CLOCKS_PER_SEC << "s" <<endl;
        cout << "+----------- TOPOLOGICAL SORT USING DFS ----------------------" << endl;
        data << "TOP: " << t1-t0 << endl;
        t0 = clock();
        // second sorting algorithm
        order = dfsSort();
        t1 = clock();
        timesIncidenceSort.push_back((double) (t1-t0)); // saves time
        // cout << "SORTED ORDER - " << f << " - DFSSORT ALGORITHM\n" << order << endl;
        cout << "CLOCK CICLES - " << (int) (t1-t0) << endl;
        cout << "TIME - " << (double) (t1-t0)/CLOCKS_PER_SEC << "s"<< endl;
        cout << "+-------------------------------------------" << "\n\n\n";
        data << "DFS: " << t1-t0 << endl;
    }
    data.close();
    gnuPlot();
}

