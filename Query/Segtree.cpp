#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

/*
* Author: Byeonggyu Park
* https://judge.yosupo.jp/problem/point_add_range_sum
* Time: 249 ms, Memory: 23.42MB
*/
struct Seg {
    vector<ll> arr; vector<ll> tree;
    int n; int sz = 1;
    ll INIT;
    /*INIT -> sum: 0, min: LLONG_MAX/2, max: -LLONG_MAX/2*/
    Seg(int n, ll ini) {
        INIT = ini;
        arr.resize(n, INIT);
        tree.resize(n << 2, INIT);
        while (sz < n) sz <<= 1;
    }
    ll op(ll a, ll b) {
        /*change to min(), max()*/
        return a + b;
    }
    /*update to arr[ind] = upd*/
    void update(int ind, ll upd) {
        arr[ind] = upd;
        ind |= sz; tree[ind] = upd;
        while (ind >>= 1) {
            tree[ind] = op(tree[ind << 1], tree[ind << 1 | 1]);
        }
    }

    ll query(int s, int e) {
        s |= sz; e |= sz;
        ll ret = INIT;
        while (s <= e) {
            if (s&1) ret = op(ret, tree[s++]);
            if (~e&1) ret = op(ret, tree[e--]);
            s>>=1; e>>=1; 
        }
        return ret;
    }
};

int main() {
    ios::sync_with_stdio(0),cin.tie(0);
    int n, q; cin >> n >> q;
    Seg seg(n, 0);
    for (int i = 0; i < n; i++) {
        cin >> seg.arr[i];
        seg.update(i, seg.arr[i]);
    }
    for (int i = 0; i < q; i++) {
        int op; cin >> op;
        ll a, b; cin >> a >> b;
        if (op == 0) {
            seg.update(a, seg.arr[a]+b);
        }
        else {
            cout << seg.query(a, b-1) << '\n';
        }
    }
}
