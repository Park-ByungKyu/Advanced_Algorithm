#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
vector<ll> arr;
vector<ll> tree;

int getindex(int index, ll upd, int l, int r, int ret) {
    if (l == r) {tree[ret] = upd; return ret;}
    int m = (l+r)/2;
    if (index <= m) return getindex(index, upd, l, m, 2*ret);
    else return getindex(index, upd, m+1, r, 2*ret+1);
}

void update(int treeind) {
    if (!treeind) return;
    if (!(treeind&1)) tree[treeind/2] = tree[treeind]+tree[treeind+1];
    else tree[treeind/2] = tree[treeind]+tree[treeind-1];
    update(treeind/2);
}

ll query(int s, int e, int l, int r, int treeind) {
    if (s <= l && r <= e) return tree[treeind];
    if (e < l || r < s) return 0;
    int m = (l+r)/2;
    return query(s,e,l,m,2*treeind)+query(s,e,m+1,r,2*treeind+1);
}

int main() {
    ios_base :: sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    ll n, m, k;
    cin >> n >> m >> k;
    arr.resize(n,0);
    tree.resize(4*n,0);
    
    for (int i = 0; i < n; i++) {
        ll p; cin >> p;
        update(getindex(i,p,0,n-1,1));
        arr[i]=p;
    }
    
    ll a,b,c;
    for (int i = 0; i < m+k; i++) {
        cin >> a >> b >> c; b--;
        if (a == 1) {
            update(getindex(b,c,0,n-1,1));
            arr[b] = c;
        } else {
            c--;
            cout << query(b, c, 0, n-1, 1) << '\n';
        }
    }
}  
