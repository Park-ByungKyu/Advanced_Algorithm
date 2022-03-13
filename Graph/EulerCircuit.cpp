#include <bits/stdc++.h>
using namespace std;

bool judge_EulerCircuit(int n, vector<vector<int>>& edge) {
    int count[n];
    for (int i = 0; i < n; i++) count[i]=0;
    for (int i = 0; i < edge.size(); i++) {
        for (int j = 0; j < edge[i].size(); j++) {
            count[i]++;
        }
    }
    for (int i = 0; i < n; i++) {
        if (count[i]&1) return false;
    } return true;
}

void print_EulerCircuit(int s, vector<vector<int>>& edge, vector<vector<int>>& edgecnt) {
    while (edge[s].size()) {
        int e = edge[s].back();
        edge[s].pop_back();
        if (edgecnt[s][e] > 0) {
            edgecnt[s][e]--;
            edgecnt[e][s]--;
            print_EulerCircuit(e, edge, edgecnt);
        }
    }
    cout << s+1 << ' ';
}

int main() {
    ios_base :: sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    
    int n; cin >> n;
    vector<vector<int>> edge;
    vector<vector<int>> edgecnt;
    edge.resize(n,vector<int>());
    edgecnt.resize(n,vector<int>(n,0));
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int a; cin >> a;
            for (int k = 0; k < a; k++) {
                edge[i].push_back(j);
            }
            edgecnt[i][j]+=a;
        }
    }
    if (!judge_EulerCircuit(n, edge)) cout << "-1";
    else print_EulerCircuit(0, edge, edgecnt);
}
