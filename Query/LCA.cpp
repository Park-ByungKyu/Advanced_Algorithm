#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base :: sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    
    int n; cin >> n;
    int level[n]; level[0]=0;
    int visited[n];
    for (int i = 0; i < n; i++) {
        visited[i]=false;
    } visited[0]=true;
    vector<int> connect[n];
    vector<int> parent[n];
    for (int i = 0; i < n-1; i++) {
        int a,b; cin >> a >> b;
        a--;b--;
        connect[a].push_back(b);
        connect[b].push_back(a);
    }
    int count = 1;
    queue<int> q1; q1.push(0);
    while (count != n) {
        int p = q1.front();
        q1.pop();
        for (int j = 0; j < connect[p].size(); j++) {
            int next = connect[p][j];
            if (visited[next] == false) {
                visited[next]=true;
                level[next] = level[p]+1;
                q1.push(next); count++;
                parent[next].push_back(p);
            }
        } 
    }

    int sparse[32][n]; sparse[0][0]=0;
    for (int i = 1; i < n; i++) {
        sparse[0][i] = parent[i][0];
    }
    for (int j = 0; j < 31; j++) {
        for (int i = 0; i < n; i++) {
            sparse[j+1][i] = sparse[j][sparse[j][i]];
        }
    }
    int query; cin >> query;
    for (int j = 0; j < query; j++) {
        int a, b; cin >> a >> b; a--; b--;
        if (level[a] < level[b]) {
            int diff = level[b]-level[a];
            int count = 0;
            while (diff != 0) {
                if (diff%2 == 1) {
                    b = sparse[count][b];
                } diff/=2; count++;
            }
        }
        if (level[a] > level[b]) {
            int diff = level[a]-level[b];
            int count = 0;
            while (diff != 0) {
                if (diff%2 == 1) {
                    a = sparse[count][a];
                } diff/=2; count++;
            }
        }
        // now level[a]==level[b]
        int left = 0; int right = level[a];
        int mid; int ta,tb;
        int ans; int anslev=-1;
        while (left <= right) {
            mid = (left+right)/2;
            ta=a; tb=b;
            int togo = level[a]-mid;
            int count = 0;
            while (togo != 0) {
                if (togo%2 == 1) {
                    ta = sparse[count][ta];
                } togo/=2; count++;
            }
            togo=level[a]-mid; count=0;
            while (togo != 0) {
                if (togo%2 == 1) {
                    tb = sparse[count][tb];
                } togo/=2; count++;
            }
            if (ta == tb) {
                if (anslev < mid) {
                    ans = ta;
                }
            }
            if (ta == tb) left = mid+1;
            else right = mid-1;
        }
        cout << ans+1 << '\n';
    }
}
