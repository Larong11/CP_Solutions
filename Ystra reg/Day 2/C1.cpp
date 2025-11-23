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

int getRes(int mandatory, vector<team> &a, vector<int> &sums) {
    int res = a[mandatory].c;

    int f = sums[a[mandatory].a] - a[mandatory].c;
    int s = sums[a[mandatory].b] - a[mandatory].c;
    
    return res + max(f, s);
}

int dfs(int u, int from, vector<vector<pair<int, int>>> &g, vector<bool> &used, int d, int start) {
    if (d == 3) {
        return 0;
    }
    used[u] = true;
    int res = 0;

    for (auto &[v, w] : g[u]) {
        if (v == from) {
            continue;
        }
        if (v == start) {
            return w;
        } else if (used[v]) {
            continue;
        }
        res = max(res, w + dfs(v, u, g, used, d + 1, start));
    }

    used[u] = false;
    return res;
}

int dfs(int u, vector<bool> &used, vector<vector<pair<int, int>>> &g, int s, int t) {
    int res = 0;
    used[u] = true;
    for (auto &[v, w] : g[u]) {
        if (t != -1) {
            if (t == v) {
                used[u] = false;
                return w;
            }
        } else {
            if (!used[v]) {
                res = max(res, dfs(v, used, g, u, s) + w);
            }
        }
    }
    used[u] = false;
    return res;
}

void solve(int n) {
    vector<vector<pair<int, int>>> g(2 * n);
    vector<int> sums(2 * n);
    vector<team> a(n);
    for (int i = 0; i < n; i++) {
        int u, v, x;
        cin >> u >> v >> x;
        --u; --v;
        a[i] = {u, v, x};

        g[u].emplace_back(v, x);
        sums[u] += x;

        g[v].emplace_back(u, x);
        sums[v] += x;
    }

    vector<pair<int, int>> p(2 * n);
    for (int i = 0; i < 2 * n; i++) {
        p[i] = {i, i};
    }

    int ans = 0;
    for (int i = 0; i < n; i++) {
        ans = max(ans, getRes(i, a, sums));
    }

    vector<bool> used(2 * n, false);
    for (int i = 0; i < 2 * n; i++) {
        ans = max(ans, dfs(i, used, g, -1, -1));
    }
    
    cout << ans << '\n';
}

int getAll(int left, int cur, vector<vector<int>> &g, vector<team> &a) {
    int res = 0;
    for (auto &v : g[cur]) {
        if (v == left) {
            continue;
        }
        res += a[v].c;
    }
    return res;
}

int getAllConnected(int left, int cur, int to, vector<vector<int>> &g, vector<team> &a) {
    int res = 0;
    for (auto &v : g[cur]) {
        if (v == left) {
            continue;
        }
        int flag = -1;

        int x = a[v].a == cur? a[v].b : a[v].a;

        for (auto &u : g[x]) {
            if (a[u].a == to or a[u].b == to) {
                flag = u;
                break;
            }
        }

        if (flag != -1) {
            res += a[v].c;
            res += a[flag].c;
        }
    }
    return res;
}

int getRes1(int mandatory, vector<team> &a, vector<vector<int>> &g) {
    int res = a[mandatory].c;

    int f = getAll(mandatory, a[mandatory].a, g, a);
    int s = getAll(mandatory, a[mandatory].b, g, a);

    int f1 = getAllConnected(mandatory, a[mandatory].a, a[mandatory].b, g, a);
    int s1 = getAllConnected(mandatory, a[mandatory].b, a[mandatory].a, g, a);

    return res + max(max(f, f1), max(s, s1));
}

void solve1(int n) {
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

    int ans = 0;

    for (int i = 0; i < n; i++) {
        ans = max(ans, getRes1(i, a, g));
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
#endif
    cin >> q;
    while (q--) {
        int n;
        cin >> n;
        if (n < 3000) {
            solve(n);
        } else {
            solve1(n);
        }
        
    }
}