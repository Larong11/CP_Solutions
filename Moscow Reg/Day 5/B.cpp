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
    int l, r, m;
    cin >> l >> r >> m;
    for (int i = l; i <= r; i++) {
        int n1 = m / i;
        int n2 = n1 + 1, n3 = n1 - 1;
        if (n1 > 0) {
            int d = m - n1 * i;
            if (0 <= d and d <= r - l) {
                cout << i << ' ' << l + d << ' ' << l << '\n';
                return;
            }
            if (d <= 0 and d >= l - r) {
                cout << i << ' ' << l << ' ' << l - d << '\n';
                return;
            }
        }
        if (n2 > 0) {
            int d = m - n2 * i;
            if (0 <= d and d <= r - l) {
                cout << i << ' ' << l + d << ' ' << l << '\n';
                return;
            }
            if (d <= 0 and d >= l - r) {
                cout << i << ' ' << l << ' ' << l - d << '\n';
                return;
            }
        }
        if (n3 > 0) {
            int d = m - n3 * i;
            if (0 <= d and d <= r - l) {
                cout << i << ' ' << l + d << ' ' << l << '\n';
                return;
            }
            if (d <= 0 and d >= l - r) {
                cout << i << ' ' << l << ' ' << l - d << '\n';
                return;
            }
        }
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