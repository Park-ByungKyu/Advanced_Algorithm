#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base :: sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	
    int n; cin >> n;
    int m = (1<<n);
    int dist[n][n];
    for (int i = 0; i < n; i++) {
	for (int j = 0; j < n; j++) cin >> dist[i][j];
    } 
    int dp[m][n];
    int visit[m];
    for (int i = 0; i < m; i++) {
        int p = i;
        int count = 0;
        while (p != 0) {
            count += (p%2);
            p/=2;
        }
        visit[i] = count;
    }
    int ans = INT_MAX;
    int start = 0;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) dp[i][j]=INT_MAX;
    }
    dp[(1<<start)][start] = 0;
    for (int p = 1; p < n; p++) {
        for (int q = 0; q < m; q++) {
            if (visit[q] == p) {
                for (int r = 0; r < n; r++) {
                    if (dp[q][r] != INT_MAX) {
                        for (int c = 0; c < n; c++) {
	                        if (q != (q|(1<<c)) && dist[r][c] != 0 && dp[q][r]+dist[r][c] < dp[(q|(1<<c))][c]) {
                                dp[(q|(1<<c))][c] = dp[q][r]+dist[r][c];
                            }
                        }
                    }
                }
            }
        }
    }
    for (int i = 0; i < n; i++) {
        if (dist[i][start] != 0 && dp[m-1][i] != INT_MAX && ans > dp[m-1][i]+dist[i][start]) ans = dp[m-1][i]+dist[i][start];
    }
    cout << ans;
} 
