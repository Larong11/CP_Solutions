#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using ld = long double;
// #define int ll
// #define double ld
const int MOD = 1e9 + 7;
const double eps = 1e-6;
const int SIGNES_AFTER_COMMA = 9;


void solve() {
    int n, m;
    cin >> n >> m;
    int mx = -1, prev = -1;
    for (int i = 0; i < m; i++) {
        int x;
        cin >> x;
        if (prev >= x) {
            mx = n;
        }
        mx = max(mx, x);
        prev = x;
    }
    cout << n - mx + 1 << '\n';
}


signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(SIGNES_AFTER_COMMA);
    int q = 1;
    cin >> q;
    while (q--) {
        solve();
    }
}