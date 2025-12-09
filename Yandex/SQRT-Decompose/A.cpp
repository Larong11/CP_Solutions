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
    int n, m;
    cin >> n >> m;
    vector<vector<int>> g(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        --u; --v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    auto cmp = [&](int a, int b) {
        return g[a].size() < g[b].size() || (g[a].size() == g[b].size() and a < b);
    };
    vector<int> p(n);
    for (int i = 0; i < n; i++) {
        p[i] = i;
    }
    sort(p.begin(), p.end(), cmp);
    for (auto &vec : g) {
        sort(vec.begin(), vec.end(), cmp);
    }
    int cnt = 0;
    vector<int> used(n, 0);
    for (auto &u : p) {
        for (auto &v : g[u]) {
            used[v]++;
        }
        for (auto &v : g[u]) {
            if (cmp(u, v)) {
                break;
            }
            for (auto &w : g[v]) {
                if (cmp(v, w)) {
                    break;
                }
                cnt += used[w];
            }
        }
        for (auto &v : g[u]) {
            used[v]--;
        }
    }
    cout << cnt << '\n';
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