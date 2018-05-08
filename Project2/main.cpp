// Created by Vitor F Dullens 16/0148260
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
#if defined(_WIN32) || defined(WIN32) || defined(__WIN32__)
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
    return result.substr(0, result.size() - 1); // pop back remove a última vírgula
    
}

void gnuPlot(vector<double> Kahn, vector<double> Dfs, vector<double> sizes){
    try{
        Gnuplot g1("lines");
        g1.set_xlabel("Size of Graphs");
        g1.set_ylabel("Time in seconds");
        g1.set_grid();
        g1.set_style("lines").plot_xy(sizes,Kahn,"Kahn's Algorithm");
        g1.set_style("lines").plot_xy(sizes, Dfs, "DFS Algorithm");
        g1.showonscreen(); // window output
        cout << "                press ENTER to continue ... " << endl;
        getchar();

    }
    catch (GnuplotException &ge){
        cout << ge.what() << endl;
    }
}

// Displays results of iteration
void showResults(string kahnOrder, string dfsOrder, int kahnClock, int dfsClock, bool showOrder = false){
        cout << "+----------- TOPOLOGICAL SORT USING KAHN ---------------------" << endl;
        if(showOrder)
            cout << "SORTED ORDER - KHANSORT ALGORITHM\n" << kahnOrder << endl;
        cout << "CLOCK CICLES - " << kahnClock << endl;
        cout << "TIME - " << (double) kahnClock/CLOCKS_PER_SEC << "s" <<endl;
        cout << "+----------- TOPOLOGICAL SORT USING DFS ----------------------" << endl;
        if(showOrder)
            cout << "SORTED ORDER -  DFSSORT ALGORITHM\n" << dfsOrder << endl;
        cout << "CLOCK CICLES - " << dfsClock << endl;
        cout << "TIME - " << (double) dfsClock/CLOCKS_PER_SEC << "s"<< endl;
        cout << "+-------------------------------------------" << "\n\n\n";
}
// Show intro
void header(){
    printf("################################################\n");
    printf("#       Projeto 2 - TAG - Unb - 2018/1         #\n");
    printf("################################################\n");
    printf("#      Aluno: Vitor F Dullens - 16/0148260     #\n");
    printf("#   Aluno: Giovanni M Guidini - 16/0122660     #\n");
    printf("################################################\n");
    printf("#               Algorithms Used                #\n");
    printf("# 1) Kahn's Algorithm:                         #\n");
    printf("# Create topological sort from incoming edges  #\n");
    printf("# of nodes. O(V+E) + time to create list of    #\n");
    printf("# incoming edges (done when reading).          #\n");
    printf("#                                              #\n");
    printf("# 2) Topological Sort with DFS:                #\n");
    printf("# Modified DFS to generate topological sort by #\n");
    printf("# adding finished nodes in a stack. The stack, #\n");
    printf("# at the end of execution, is a valid          #\n");
    printf("# topological sort. O(V+E).  With that been    #\n");
    printf("# said this algorithm is more recommended for  #\n");
    printf("# this exercise, because in almost all the     #\n");
    printf("# situations it performs better.               #\n");                            
    printf("################################################\n");
    printf("\n");
    cout << "                press ENTER to continue ... " << endl;
    getchar(); cout << "\n\n";
}

int main(){
    header();
    // save execution times to create comprehensive study
    // ofstream data;
    // data.open("data.txt", ios::app);
    vector<double> timesIncidenceSort;
    vector<double> timesDFSSort;
    vector<double> sizes;
    // the 4 graphs
    vector<string> files = {"top_small.txt", "top_med.txt", "top_large.txt", "top_huge.txt"};
    // execute main loop for all graphs
    for (auto f : files){
        cout << "Processando arquivo " << f << endl;
        string path = "top_datasets" + (SLASH + f);
        // reads graph + creates incidency list
        readGraph(path);
        sizes.push_back(size);

        clock_t t0 = clock();
        // first sorting algorithm
        string kahn = kahnSort();
        clock_t t1 = clock();
        timesIncidenceSort.push_back((double) (t1-t0)/CLOCKS_PER_SEC); // saves time
        int kahnClock = t1-t0;
        
        t0 = clock();
        // second sorting algorithm
        string dfs = dfsSort();
        t1 = clock();
        timesDFSSort.push_back((double) (t1-t0)/CLOCKS_PER_SEC); // saves time
        int dfsClock = t1-t0;
        
        // showResults(kahn, dfs, kahnClock, dfsClock); // show results on screen, whitout showing order.
        showResults(kahn, dfs, kahnClock, dfsClock, true); // comment if want to see results without ordering

        //Saving data for further analysis
        //data << size << endl;  // size of run
        //data << "TOP: " << kahnClock << endl;
        //data << "DFS: " << dfsClock << endl;
    }
    // data.close();
    // quick summary of results
    int k = 0, d = 0;
    for(int i = 0; i < 4; i++){
        if(timesDFSSort[i] < timesIncidenceSort[i])
            d++;
        else
            k++;
    }
    cout << "Summary:\n";
    cout << "DFS Sort was faster in " << d << " test cases\n";
    cout << "Khan's Sort was faster or equal to DFS in " << k << " test cases\n";
    gnuPlot(timesIncidenceSort, timesDFSSort, sizes);
}

