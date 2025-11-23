#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using ld = long double;
#define int ll
#define double ld
const int MOD = 1e9 + 7;
const double eps = 1e-6;
const int SIGNES_AFTER_COMMA = 9;

struct team {
    int a, b, c;
};

int gen(int i, vector<vector<int>> &g, vector<team> &a, set<int> &cur, set<int> &possible, vector<bool> &used) {
    int res = 0;
    
    if (used[i]) {
        return 0;
    }
    
    for (auto &j : cur) {
        if (a[i].a != a[j].a and a[i].a != a[j].b and
            a[i].b != a[j].a and a[i].b != a[j].b) {
                return 0;
            }
    }
    
    auto res2 = cur.insert(i);
    auto res1 = possible.erase(i);
    
    used[i] = true;

    res += a[i].c;
    for (auto &u : g[a[i].a]) {
        if (!used[u] and u > i) 
            possible.insert(u);
    }
    for (auto &u : g[a[i].b]) {
        if (!used[u] and u > i)
            possible.insert(u);
    }
    vector<int> pos;
    for (auto &j : possible) {
        if (j > i)
            pos.push_back(j);
    }
    for (auto &j : pos) {
        res = max(res, a[i].c + gen(j, g, a, cur, possible, used));
    }

    if (res1) {
        possible.insert(i);
    }
    if (res2.second) {
        cur.erase(res2.first);
    }
    used[i] = false;
    return res;
}

void solve() {
    int n;
    cin >> n;
    vector<vector<int>> g(2 * n);
    vector<team> a(n);
    for (int i = 0; i < n; i++) {
        int u, v, x;
        cin >> u >> v >> x;
        --u; --v;
        a[i] = {u, v, x};
        g[u].push_back(i);
        g[v].push_back(i);
    }
    int res = 0;
    set<int> cur, possible;
    vector<bool> used(n, false);
    for (int i = 0; i < n; i++) {
        res = max(res, gen(i, g, a, cur, possible, used));
    }
    cout << res << '\n';
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout << fixed << setprecision(SIGNES_AFTER_COMMA);
    int q = 1;
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    cin >> q;
    while (q--) {
        solve();
    }
}