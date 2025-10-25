#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using ld = long double;
#define int ll
#define double ld
const int MOD = 1e9 + 7;
const double eps = 1e-6;
const int SIGNES_AFTER_COMMA = 9;

void dfs(int u, vector<vector<int>> &g, vector<bool> &used, int s, int t, int &ans) {
    for (int &v : g[u]) {
        if (used[v]) {
            if (t == v) {
                ans++;
            }
        } else {
            dfs(v, g, used, u, s, ans);
        }
    }
}

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
    int ans = 0;
    vector<bool> used(n);
    for (int i = 0; i < n; i++) {
        if (!used[i]) {
            dfs(i, g, used, -1, -1, ans);
        }
    }
    cout << ans / 6 << '\n';
}


signed main() {
    int q = 1;
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    cin >> q;
#endif
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(SIGNES_AFTER_COMMA);
    while (q--) {
        solve();
    }
}