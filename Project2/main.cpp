// Created by Vitor F Dullens 
// and Giovanni M Guidini 16/0122660
#include <bits/stdc++.h>

using namespace std;

// graph
vector<int> G[1000000];
vector<int> IN(1000000);
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

int main(){
    vector<string> files = {"top_small.txt", "top_med.txt", "top_large.txt", "top_huge.txt"};
    for(auto f : files){
        cout << "Processando arquivo " << f << endl;
        string path = "top_datasets/" + f;
        readGraph(path);
        clock_t t0 = clock();
        string order = topSort();
        clock_t t1 = clock();
        int delta = t1-t0;
        cout << "SORTED ORDER\n" << order << endl;
        printf("CLOCK CICLES: %lf\n", delta); 
        cout << t0 << " " << t1 << endl;
    }
}

