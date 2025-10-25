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
    int n, x;
    cin >> n >> x;
    int sum = 0;
    vector<int> a(n);
    for (auto &i : a) {
        cin >> i;
        sum += i;
    }
    int idx = -1;
    for (int i = 0; i < n; i++) {
        if (-(sum - a[i]) + (n - 1) * a[i] == x) {
            idx = i;
            break;
        }
    }
    if (idx == -1) {
        cout << -1 << '\n';
    } else {
        swap(a.back(), a[idx]);
        for (auto &i : a) {
            cout << i << ' ';
        }
        cout << '\n';
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