#include <bits/stdc++.h>

using namespace std;


int color[1001];
vector<int> grafo[1001];

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


int main(){
    int n;
    cin >> n;
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= n; j++){
            int x;
            cin >> x;
            if(!x and i != j)
                grafo[i].push_back(j);
            
        }
    }
    memset(color, -1, sizeof(color));

    for(int i = 1; i <= n; i++)
        if(color[i] == -1)
            if(!bipartite(i)) return puts("Fail!"),0;

    
    cout << "Bazinga!" << endl;
    return 0;

}