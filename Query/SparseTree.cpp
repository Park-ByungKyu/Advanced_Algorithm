#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base :: sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    
    // Make Sparse Tree
    int m; cin >> m;
    int sparse[32][m+1];
    for (int i = 0; i < m; i++) {
        cin >> sparse[0][i+1];
    }
    for (int j = 0; j < 31; j++) {
        for (int k = 1; k < m+1; k++) {
            sparse[j+1][k] = sparse[j][sparse[j][k]];
        }
    }
    
    // Query
    int q, n, x; cin >> q;
    for (int i = 0; i < q; i++) {
        cin >> n >> x;
        int ans = x;
        int count = 0;
        while (n>0) {
            if (n&1) ans = sparse[count][ans];
            n>>=1; count++;
        }
        cout << ans << '\n';
    }
}
