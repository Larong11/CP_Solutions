#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using ld = long double;
#define int ll
#define double ld
const int MOD = 1e9 + 7;
const double eps = 1e-6;
const int SIGNES_AFTER_COMMA = 9;
const ll INF = 1e12;

void solve() {
    int n, m, k;
    cin >> n >> m >> k;
    vector<vector<pair<int, int>>> g(n);
    for (int i = 0; i < m; i++) {
        int u, v, t;
        cin >> u >> v >> t;
        --u; --v;
        g[u].emplace_back(v, t);
        g[v].emplace_back(u, t);
    }
    vector<int> dists(n, INF);
    dists[n - 1] = 0;
    bool flag = true;
    while (flag) {
        flag = false;
        for (int i = 0; i < n; i++) {
            vector<pair<int, int>> mins;
            for (auto &[v, w] : g[i]) {
                mins.emplace_back(w + dists[v], w);
            }
            sort(mins.begin(), mins.end());
            int minim = INF;
            for (int j = 0; j < min(k, (int)mins.size()); j++) {
                minim = min(minim, mins[j].first + mins[j].second);
            }
            if (k < mins.size()) {
                minim = min(minim, mins[k].first);
            }
            if (minim < dists[i]) {
                dists[i] = minim;
                flag = true;
            }
        }
    }
    cout << (dists[0] == INF? -1 : dists[0]) << '\n';
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