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
    int a, b;
    cin >> a >> b;
    int ja = a / n, jb = b / n, ia, ib;
    if (!(ja & 1)) {
        ia = n - (a - ja * n) - 1;
    } else {
        ia = (a - ja * n);
    }
    if (!(jb & 1)) {
        ib = n - (b - jb * n) - 1;
    } else {
        ib = b - jb * n;
    }
    ia++;
    ib++;
    ja = n - ja;
    jb = n - jb;
    cout << ja << ' '<< ia << '\n';
    cout << jb << ' ' << ib << '\n';
    cout << abs(ia - ib) + abs(ja - jb) << '\n';
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