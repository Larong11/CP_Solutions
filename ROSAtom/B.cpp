#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using ld = long double;
#define int ll
#define double ld
const int MOD = 1e9 + 7;
const double eps = 1e-6;
const int SIGNES_AFTER_COMMA = 9;

double dfs(int u, int n, vector<vector<int>> &g, int d, double possibility) {
    double res = 0;
    int k = g[u].size();
    for (int i = 0; i < k; i++) {
        if (i < n % k) {
            res += dfs(g[u][i], n, g, d + 1, possibility * double((n + k - 1) / k) / double(n));
        } else {
            res += dfs(g[u][i], n, g, d + 1, possibility * double(n / k) / double(n));
        }
    }
    if (k == 0) {
        res = double(d) * possibility;
    }
    return res;
}

void solve() {
    int n;
    cin >> n;
    int m;
    cin >> m;
    vector<vector<int>> g(m);
    for (int i = 0; i < m; i++) {
        int k;
        cin >> k;
        for (int j = 0; j < k; j++) {
            int x;
            cin >> x;
            --x;
            g[i].push_back(x);
        }
    }
    cout << dfs(0, n, g, 0, 1) << '\n';
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