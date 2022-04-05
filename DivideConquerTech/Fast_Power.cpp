#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
ll Fast_Power (ll x, ll y, ll mod) { // (x^y)%mod
    vector<ll> zegob;
    zegob.resize(64,1);
    zegob[0] = x;
    for (int i = 1; i < 64; i++) {
        zegob[i] = (zegob[i-1] * zegob[i-1]) % mod;
    }
    ll ans = 1;
    for (int i = 0; i < 64; i++) {
        if (y&1) {
            ans = (ans * zegob[i]) % mod;
        }
        y>>=1;
    }
    return ans;
}

int main() {
    ios_base :: sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    
    ll a, b, c; 
    cin >> a >> b >> c;
    
    cout << Fast_Power(a,b,c);
}
