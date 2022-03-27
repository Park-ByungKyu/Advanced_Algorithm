#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
vector<ll> arr;
vector<ll> tree;
vector<ll> lazy;

void update(int s, int e, ll upd, int l, int r, int treeind) {
    int m = (l+r)/2;
    if (s <= l && r <= e) {
        lazy[treeind] += upd; return;
    }
    if (e < l || r < s) return;
    
    ll range = min(e,r)-max(s,l)+1;
    tree[treeind] += range * upd;
    update(s,e,upd,l,m,treeind*2);
    update(s,e,upd,m+1,r,treeind*2+1);
}

ll query(int s, int e, int l, int r, int treeind) {
    if (lazy[treeind]) {
        tree[treeind] += (lazy[treeind] * (r-l+1));
        if (treeind*2 < lazy.size()) lazy[treeind*2] += lazy[treeind];
        if (treeind*2+1 < lazy.size()) lazy[treeind*2+1] += lazy[treeind];
        lazy[treeind] = 0;
    }
    int m = (l+r)/2;
    if (s <= l && r <= e) return tree[treeind];
    if (e < l || r < s) return 0;
    return query(s,e,l,m,2*treeind)+query(s,e,m+1,r,2*treeind+1);
}

int main() {
    ios_base :: sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    ll n, m, k, a, b, c;
    cin >> n >> m >> k;
    arr.resize(n,0);
    tree.resize(4*n,0);
    lazy.resize(4*n,0);
    
    for (int i = 0; i < n; i++) {
        ll p; cin >> p;
        update(i, i, p, 0, n-1, 1);
        arr[i]=p;
    }
    for (int i = 0; i < m+k; i++) {
        cin >> a >> b >> c; b--; c--;
        if (a == 1) {
            ll d; cin >> d;
            update(b, c, d, 0, n-1, 1);
            arr[b] = c;
        } else {
            cout << query(b, c, 0, n-1, 1) << '\n';
        }
    }
}  
