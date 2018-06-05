#include <bits/stdc++.h>
using namespace std;

#define MAX_V 1500
class edge {

public:
    int source;
    int target;
    int weight;

    edge(int s, int t, int w = 0){
        source = s;
        target = t;
        weight = w;
    }
};

// tudo global mesmo porque ninguem quer função com 40 mil parametros
vector<edge> blk;
vector<edge> G[MAX_V];
vector<int> low;
vector<int> start;
vector<int> parent;
vector<bool> visited;

void blocks(int i, int d){
    // cout << "I: " << i << " D: " << d << endl;
    visited[i] = true;
    start[i] = low[i] = d; // muito louco isso :D
    vector<edge> ni = G[i]; // neighbours
    int child = 0;

    for(edge e : ni){
        int u = e.target;
        if(!visited[u]){
            parent[u] = i;
            // cout << "Adding edge: " << e.source << "--" << e.target << endl;
            blk.push_back(edge(i, u));
            blocks(u, ++d);
            child++;
                    // articulation points                  root is special case
            if((start[i] > 0 && low[u] >= start[i]) || (start[i] == 0 && child > 1)){
                // achou o vertice de corte deste bloco
                edge k = blk.back(); blk.pop_back();
                while(k.source != i || k.target != u){
                    cout << k.source << "--" << k.target << " ";
                    k = blk.back(); blk.pop_back();
                }
                // last edge in block
                cout << k.source << "--" << k.target << endl;
            }
            low[i] = min(low[i], low[u]);
        }
        else if (u != parent[i]){
            // cout << "NO else if i: " << i << " u: " << u << endl;
            // cout << "start[u] " << start[u] << " vs. low[i] " << low[i] << endl;
            if(start[u] < low[i]){
                // cout << "Adding edge: " << e.source << "--" << e.target << endl;
                blk.push_back(edge(i, u));
            }
            low[i] = min(low[i], start[u]);
        }
    }
}

void findBlocks(int size){
    low.resize(size, 0);
    start.resize(size, 0);
    parent.resize(size, -1);
    visited.resize(size, false);
    int d = 0;

    for(int i = 0; i < size; i++){
        if(!visited[i])
            blocks(i, d++);
    }

    // if the last block is not printed
    while(blk.size() > 0){
        edge k = blk.back(); blk.pop_back();
        cout << k.source << "--" << k.target << " ";
    }
}

int main(){
    ifstream fd ("graph.txt");
    if(!fd){
        exit(1);
    }
    int n, s, t;
    fd >> n;
    while(fd >> s >> t){
        // nao direcionado
        G[s].push_back(edge(s, t));
        G[t].push_back(edge(t,s));
    }

    findBlocks(n);
    cout << endl;
}