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
    int n;
    cin >> n;
    int zeros = 0, minus = 0;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        if (x == 0) {
            zeros++;
        } else if (x == -1) {
            minus++;
        }
    }
    cout << zeros + (minus & 1) * 2 << '\n' << '\n';;
}


signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(SIGNES_AFTER_COMMA);
    int q = 1;
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    cin >> q;
    while (q--) {
        solve();
    }
}