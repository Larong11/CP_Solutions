#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using ld = long double;
#define int ll
#define double ld
const int MOD = 1e9 + 7;
const double eps = 1e-6;
const int SIGNES_AFTER_COMMA = 9;

void dfs(int u, int from, vector<vector<int>> &g, vector<int> &dp) {
    for (auto &v : g[u]) {
        if (v == from) {
            continue;
        }
        dfs(v, u, g, dp);
        dp[u] = max(dp[v] + 1, dp[u]);
    }
}

void createAns(int u, int from, int d, int &ans, vector<vector<int>> &g, vector<int> &dp, vector<int> &depth) {
    depth[d] = u;
    int curAns = 0;
    if (d == 0) {
        curAns = 0;
    } else if (d == 1) {
        curAns = 1;
    } else {
        int upOn = d / 2 - 1;
        curAns = dp[depth[d - upOn]] + d - upOn;
    }
    cout << u + 1 << " " << curAns << '\n';
    ans += curAns;
    for (auto &v : g[u]) {
        if (v == from) {
            continue;
        }
        createAns(v, u, d + 1, ans, g, dp, depth);
    }
}

void solve() {
    int n;
    cin >> n;
    vector<vector<int>> g(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        --u; --v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    vector<int> dp(n, 0);
    dfs(6, -1, g, dp);
    int ans = 0;
    vector<int> depth(n);
    createAns(6, -1, 0, ans, g, dp, depth);
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