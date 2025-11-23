#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using ld = long double;
#define int ll
#define double ld
const int MOD = 1e9 + 7;
const double eps = 1e-6;
const int SIGNES_AFTER_COMMA = 9;

void dfsSort(int u, vector<vector<int>> &g, vector<bool> &used, vector<int> &topSort) {
    if (used[u]) {
        return;
    }
    used[u] = true;
    for (auto &v : g[u]) {
        dfsSort(v, g, used, topSort);
    }
    topSort.push_back(u);
}

void dfsComponents(int u, vector<vector<int>> &t, vector<int> &comps, int compNum) {
    if (comps[u] != 0) {
        return;
    }
    comps[u] = compNum;
    for (auto &v : t[u]) {
        dfsComponents(v, t, comps, compNum);
    }
}

void solve() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> g(n);
    vector<vector<int>> t(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        --u; --v;
        g[u].push_back(v);
        t[v].push_back(u);
    }
    vector<bool> used(n);
    vector<int> topSort;
    for (int i = 0; i < n; i++) {
        if (!used[i]) {
            dfsSort(i, g, used, topSort);
        }
    }
    reverse(topSort.begin(), topSort.end());
    vector<int> comps(n);
    int numComps = 0;
    for (auto &i : topSort) {
        if (comps[i] == 0) {
            dfsComponents(i, t, comps, numComps + 1);
            numComps++;
        }
    }
    cout << numComps << '\n';
    for (auto &i : comps) {
        cout << i << ' ' ;
    }
    cout << '\n';
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