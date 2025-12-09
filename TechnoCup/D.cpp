#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using ld = long double;
#define int ll
#define double ld
const int MOD = 1e9 + 7;
const double eps = 1e-6;
const int SIGNES_AFTER_COMMA = 9;

void solve() {
    string a; 
    cin >> a; 
    int n = a.size(); 
    string b = ""; 
    for (int i = 0; i < n; i++) { 
        string prefix = a.substr(0, i); 
        string suffix = a.substr(n - i, i); 
        if (prefix == suffix) { 
            b = a.substr(i);
            reverse(b.begin(), b.end()); 
            break; 
        } 
    } 
    cout << b << endl; 
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout << fixed << setprecision(SIGNES_AFTER_COMMA);
    int q = 1;
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    cin >> q;
#endif
    while (q--) {
        solve();
    }
}