#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> scc;
vector<int> discovered;
vector<bool> finished;
int cnt = 0;
stack<int> stk;
vector<vector<int>> edge;

int SCC(int s) {
    discovered[s] = ++cnt;
    int state = discovered[s];
    stk.push(s);
    for (int i = 0; i < edge[s].size(); i++) {
        int e = edge[s][i];
        if (!discovered[e]) state = min(state, SCC(e));
        else if (!finished[e] && discovered[e] < state) state = discovered[e];
    }
    if (state == discovered[s]) {
        vector<int> onescc;
        int t = -1;
        while (t != s) {
            t = stk.top(); stk.pop();
            finished[t] = true;
            onescc.push_back(t);
        }
        scc.push_back(onescc);
    }
    return state;
}

void SCC_all(int V) {
    for (int i = 0; i < V; i++) {
        if (!discovered[i]) SCC(i);
    }
}

int main() {
    ios_base :: sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    
    int V, E; cin >> V >> E;
    edge.resize(V,vector<int>());
    int s,e;
    for (int i = 0; i < E; i++) {
        cin >> s >> e;
        edge[s-1].push_back(e-1);
    }
    discovered.resize(V,0);
    finished.resize(V,false);
    
    SCC_all(V);
    cout << scc.size() << '\n';
    for (int i = 0; i < scc.size(); i++) {
        sort(scc[i].begin(), scc[i].end());
    } sort(scc.begin(), scc.end());
    for (int i = 0; i < scc.size(); i++) {
        for (int j = 0; j < scc[i].size(); j++) {
            cout << scc[i][j]+1 << ' ';
        } cout << "-1\n"; 
    }
}
