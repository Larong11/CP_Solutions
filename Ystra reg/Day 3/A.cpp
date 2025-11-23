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
    vector<int> a(n);
    for (auto &i : a) {
        cin >> i;
    }
    int q;
    cin >> q;
    vector<pair<int, int>> c;
    for (int i = 0; i < q; i++) {
        int s, e;
        cin >> s >> e;
        c.emplace_back(s - 1, e);
    }
    sort(c.begin(), c.end());
    multiset<pair<int, int>> b1;
    int idx = 0;
    int ans = 0;
    for (int i = 0; i < n; i++) {
        while (!b1.empty() and b1.begin()->first <= i) {
            b1.erase(b1.begin());
        }
        while (idx < c.size() and c[idx].first <= i) {
            b1.insert({c[idx].second, c[idx].first});
            idx++;
        }
        while (b1.size() > a[i]) {
            b1.erase(--b1.end());
            ans++;
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

// 100 - 4:47:00