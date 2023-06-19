#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

vector<vector<int>> edge;
vector<int> level;
vector<vector<int>> sparse;

void solve_level_sparse(int n, int root) {
    queue<int> q;
    sparse[root][0] = root; level[root] = 0;
    q.push(root);
    while (!q.empty()) {
        int s = q.front(); q.pop();
        for (int i = 0; i < edge[s].size(); i++) {
            int e = edge[s][i];
            if (level[e] == -1) {
                sparse[e][0] = s;
                level[e] = level[s]+1;
                q.push(e);
            }
        }
    }
    for (int j = 0; j < 31; j++) {
        for (int i = 0; i < n; i++) {
            sparse[i][j+1] = sparse[sparse[i][j]][j];
        }
    }
}

int lca(int a, int b) {
    if (level[a] < level[b]) swap(a, b);
	int diff = level[a]-level[b];
    
	for(int i = 0; diff; i++){
		if (diff&1) a = sparse[a][i];
		diff >>= 1;
	}
	if (a == b) return a;

	for (int i = 31; i >= 0; i--){
		if (sparse[a][i] != sparse[b][i]) a = sparse[a][i], b = sparse[b][i];
	}
	return sparse[a][0];
}

int main() {
    ios_base :: sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    int n; cin >> n;
    edge.resize(n, vector<int>());
    level.resize(n, -1);
    sparse.resize(n, vector<int>(32, -1));
    
    for (int i = 0; i < n-1; i++) {
        int a, b, w; cin >> a >> b;
        a--; b--;
        edge[a].push_back(b);
        edge[b].push_back(a);
    }
    solve_level_sparse(n, 0);
    
    int m; cin >> m;
    for (int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        a--; b--;
        cout << lca(a, b)+1 << '\n';
    }
}