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
    int c, v, l, r;
    cin >> c >> v >> l >> r;
    int sum = 0;
    if (l == 1) {
        sum += 1;
        l = 3;
    }
    if (l <= 3 and r >= 3) {
        sum += c;
        l = 5;
    }
    if (r >= 5) {
        if (((r - l + 1 + (l & 1)) / 2) % 2 == 0 or c % 2 == 0 or v % 2 == 0) {
            sum += 2;
        } else {
            sum += 1;
        }
    }
    if (sum & 1) {
        cout << "King" << '\n';
    } else {
        cout << "Queen" << '\n';
    }
}


signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
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