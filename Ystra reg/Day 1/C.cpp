#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using ld = long double;
#define int ll
#define double ld
const int MOD = 1e9 + 7;
const double eps = 1e-6;
const int SIGNES_AFTER_COMMA = 9;

void getParents(int u, int from, vector<int> &p, vector<int> &sz, vector<vector<pair<int, int>>> &g) {
    sz[u] = 0;
    p[u] = from;
    for (auto &[v, w] : g[u]) {
        if (v != from) {
            getParents(v, u, p, sz, g);
            sz[u] = max(sz[u], w + sz[v]);
        }
    }
}

int dfs(int u, int from, int &restricted, vector<vector<pair<int, int>>> &g, vector<int> &p, vector<int> &sz, bool flag) {
    int ans = 0;
    int ans2 = 0;
    for (auto &[v, w] : g[u]) {
        if (v == from or v == restricted) {
            continue;
        }
        int val;
        if (v == p[u]) {
            val = w + dfs(v, u, restricted, g, p, sz, false);
        } else {
            val = w + sz[v];
        }
        if (val > ans) {
            ans2 = ans;
            ans = val;
        } else if (val > ans2) {
            ans2 = val;
        }
    }
    return flag? ans + ans2 : ans;
}

void dep(int u, int from, vector<vector<pair<int, int>>> &g, vector<int> &depths, int d) {
    depths[u] = d;
    for (auto &[v, w] : g[u]) {
        if (v != from) {
            dep(v, u, g, depths, d + w);
        }
    }
}

void solve() {
    int n, q;
    cin >> n >> q;
    vector<vector<pair<int, int>>> g(n);
    bool secondGroup = true;
    bool firstGroup = true;
    for (int i = 0; i < n - 1; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        --u; --v;
        if ((u != 0 and v != 0) or w != 1) {
            secondGroup = false;
        }
        if (abs(u - v) != 1 or w != 1) {
            firstGroup = false;
        }
        g[u].emplace_back(v, w);
        g[v].emplace_back(u, w);
    }
    if (!firstGroup) {
        vector<int> parents(n, -2);
        vector<int> sz(n, 0);
        getParents(0, -1, parents, sz, g);
        for (int _ = 0; _ < q; _++) {
            int a, b;
            cin >> a >> b;
            --a; --b;
            if (secondGroup) {
                if (a == b and a != 0) {
                    cout << 0 << '\n';
                } else if (b == 0) {
                    cout << 2 << '\n';
                }
            } else {
                cout << dfs(a, -1, parents[b], g, parents, sz, true) << '\n';
            }
        }
    } else {
        vector<int> depths(n);
        dep(0, -1, g, depths, 0);
        int maxDepth = 0;
        for (auto &i : depths){ 
            maxDepth = max(maxDepth, i);
        }
        for (int i = 0; i < q; i++) {
            int a, b;
            cin >> a >> b;
            --a; --b;
            cout << maxDepth - depths[b] << '\n';
        }
    }
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