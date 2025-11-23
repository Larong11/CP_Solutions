#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using ld = long double;
#define int ll
#define double ld
const int MOD = 1e9 + 7;
const double eps = 1e-6;
const int SIGNES_AFTER_COMMA = 9;

void dfs(int u, int from, vector<vector<pair<int, int>>> &g, vector<int> &enter, vector<int> &ret, int t, vector<int> &bridges) {
    t += 1;
    enter[u] = t;
    ret[u] = t;
    for (auto &[v, i] : g[u]) {
        if (v == from) {
            ret[u] = min(ret[u], enter[v]);
        } else if (enter[v] == -1) {
            dfs(v, u, g, enter, ret, t, bridges);
            ret[u] = min(ret[u], ret[v]);
            if (ret[v] > enter[u]) {
                bridges.push_back(i);
            }
        }
    }
}

int cnt(int u, int &from, vector<vector<pair<int, int>>> &g, vector<bool> &used) {
    if (used[u] or u == from) {
        return 0;
    }
    int ans = 0;
    for (auto &[v, i] : g[u]) {
        ans += cnt(v, from, g, used);
    }
    return ans;
}

void solve() {
    int n, m;
    cin >> n >> m;
    vector<vector<pair<int, int>>> g(n);
    vector<pair<int, int>> edges;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        --u; --v;
        g[u].emplace_back(v, i);
        g[v].emplace_back(u, i);
        edges.emplace_back(u, v);
    }
    vector<int> enter(n, -1), ret(n, -1), bridges;
    dfs(0, -1, g, enter, ret, 0, bridges);
    int ans = 0;
    vector<bool> used(n, false);
    for (auto &i : bridges) {
        auto [u, v] = edges[i];
        used.assign(n, false);
        int x = cnt(v, u, g, used);
        ans += x * (n - x);
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