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
    if (n < 8 or n == 9) {
        cout << -1 << '\n';
    } else if (n == 8) {
        cout << 7 << ' ' << 7 << '\n';
    } else {
        int x = (n - 8) / 8;
        int cnt = 8 - ((n - 8) - (x * 8));
        int a = ((x * (x - 1)) / 2 + x) * cnt;
        int y = (n - 8 + 7) / 8;
        int b = ((y * (y - 1)) / 2 + y) * cnt;
        cout << a + b + 7 << ' ' << 7 + (n - 8) + (n - 8) * (n - 9) / 2 << '\n';
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