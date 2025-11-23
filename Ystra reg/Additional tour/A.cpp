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
    vector<pair<int, int>> a(n);
    for (auto &i : a) {
        cin >> i.first >> i.second;
    }
    sort(a.begin(), a.end());
    int ans = 0;
    for (int i = 0; i < n; i++) {
        if (a[i].first <= x) {
            x += a[i].second;
            ans++;
        } else {
            break;
        }
    }
    cout << ans << '\n';
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