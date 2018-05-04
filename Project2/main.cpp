// Created by Vitor F Dullens 
// and Giovanni M Guidini 16/0122660
#include <bits/stdc++.h>

using namespace std;

// graph
vector<int> G[1000000];
vector<int> IN(1000000);
stack<int> P;
int size;


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

// topological sort using incindency list of nodes
string topSort(){
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

int main(){
    // {"top_small.txt", "top_med.txt", "top_large.txt", "top_huge.txt"};
    // vector<string> files = {"top_small.txt", "top_med.txt"};
    vector<string> files = {"top_small.txt", "top_med.txt", "top_large.txt", "top_huge.txt"};
    for (auto f : files){
        cout << "Processando arquivo " << f << endl;
        string path = "top_datasets/" + f;
        readGraph(path);
        clock_t t0 = clock();
        string order = topSort();
        clock_t t1 = clock();
        cout << "+-------------------------------------------" << endl;
        cout << "SORTED ORDER - " << f << " - TOPSORT ALGORITHM\n" << order << endl;
        cout << "CLOCK CICLES - " << f << " - TOPSORT ALGORITHM: " << t1 - t0;
        cout << " \t\tt0 = " << t0 << " " << "t1 = " << t1 << endl;
        cout << "+-------------------------------------------" << endl;
        t0 = clock();
        order = dfsSort();
        t1 = clock();
        cout << "SORTED ORDER - " << f << " - DFSSORT ALGORITHM\n" << order << endl;
        cout << "CLOCK CICLES - " << f << " - DFSSORT ALGORITHM: " << t1 - t0;
        cout << " \t\tt0 = " << t0 << " " << "t1 = " << t1 << "\n";
        cout << "+-------------------------------------------" << "\n\n\n";
    }
}

