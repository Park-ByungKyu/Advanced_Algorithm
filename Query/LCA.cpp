#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> edge;
vector<int> parent;
vector<int> level;
vector<vector<int>> sparse;

void solve_parent_level_sparse(int n, int root) {
    queue<int> q;
    parent[root] = root; level[root] = 0;
    q.push(root);
    while (!q.empty()) {
        int s = q.front(); q.pop();
        for (int i = 0; i < edge[s].size(); i++) {
            int e = edge[s][i];
            if (level[e] == -1) {
                parent[e] = s;
                level[e] = level[s]+1;
                q.push(e);
            }
        }
    }
    for (int i = 0; i < n; i++) {
        sparse[i][0] = parent[i];
    }
    for (int j = 0; j < 31; j++) {
        for (int i = 0; i < n; i++) {
            sparse[i][j+1] = sparse[sparse[i][j]][j];
        }
    }
}

int lca(int a, int b) {
    int diff = abs(level[b]-level[a]);
    int cnt = 0;
    while (diff != 0) {
        if (diff%2 != 0) {
            if (level[b]-level[a] > 0) b = sparse[b][cnt];
            else a = sparse[a][cnt];
        }
        diff>>=1; cnt++;
    }
    // now level[a]==level[b]
    int l = 0; int r = level[a];
    int mid; int ta,tb;
    int ans;
    while (l <= r) {
        mid = (l+r)/2;
        ta=a; tb=b;
        int togo = level[a]-mid;
        int count = 0;
        while (togo != 0) {
            if (togo&1) {
                ta = sparse[ta][count];
                tb = sparse[tb][count];
            } 
            togo>>=1; count++;
        }
        if (ta == tb) {
            ans = ta; l = mid+1;
        }
        else r = mid-1;
    }
    return ans;
}

int main() {
    ios_base :: sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    
    int n; cin >> n;
    edge.resize(n, vector<int>());
    parent.resize(n, -1);
    level.resize(n, -1);
    sparse.resize(n, vector<int>(32, -1));
    
    for (int i = 0; i < n-1; i++) {
        int a, b; cin >> a >> b;
        edge[a-1].push_back(b-1);
        edge[b-1].push_back(a-1);
    }
    solve_parent_level_sparse(n, 0);
    
    int m; cin >> m;
    for (int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        int ans = lca(a-1, b-1);
        cout << ans+1 << '\n';
    }
}