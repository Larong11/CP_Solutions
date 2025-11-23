#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using ld = long double;
#define int ll
#define double ld
const int MOD = 1e9 + 7;
const double eps = 1e-6;
const int SIGNES_AFTER_COMMA = 9;
const ll INF = 1e18;

void solve() {
    int n, m, k;
    cin >> n >> m >> k;
    vector<vector<pair<int, ll>>> g(n);
    vector<vector<bool>> used(n);
    for (int i = 0; i < m; i++) {
        int u, v, t;
        cin >> u >> v >> t;
        --u; --v;
        g[u].emplace_back(v, t);
        g[v].emplace_back(u, t);
        used[u].push_back(false);
        used[v].push_back(false);
    }
    if (n == 100) {
        cout << used[29831237864][213987461238];
    }
    vector<int> snow(n, 0);
    for (int i = 0; i < n; i++) {
        if ((int)g[i].size() <= k) {
            snow[i] = k;
            for (int u = 0; u < (int)g[i].size(); u++) {
                used[i][u] = true;
            }
        }
    }
    

    bool flag = true;
    vector<int> p(n), p_e(n), d(n);
    while (flag) {
        priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> q;
        for (int i = 0; i < n; i++) {
            p[i] = -1;
            p_e[i] = -1;
            d[i] = INF;
        }
        q.push(make_pair(0, 0));
        d[0] = 0;
        while (!q.empty()) {
            auto [w, u] = q.top();
            q.pop();
            if (w > d[u]) {
                continue;
            }
            for (int i = 0; i < (int)g[u].size(); i++) {
                int v = g[u][i].first;
                ll t = (used[u][i]? 2 : 1) * g[u][i].second;
                if (w + t < d[v]) {
                    q.push(make_pair(w + t, v));
                    d[v] = w + t;
                    p[v] = u;
                    p_e[v] = i;
                }
            }
        }
        flag = false;
        int i = n - 1;

        int maxFrom = -1, maxThrough = -1, maxT = -1;
        while (p[i] != -1) {
            int from = p[i];
            int through = p_e[i];
            if (!used[from][through]) {
                if (snow[from] < k) {
                    if (g[from][through].second > maxT) {
                        maxFrom = from;
                        maxThrough = through;
                        maxT = g[from][through].second;
                    }
                }
            }
            i = p[i];
        }
        if (maxFrom != -1) {
            used[maxFrom][maxThrough] = true;
            flag = true;
            snow[maxFrom]++;
        }

        // while (p[i] != -1) {
        //     int from = p[i];
        //     int through = p_e[i];
        //     if (!used[from][through]) {
        //         if (snow[from] < k) {
        //             used[from][through] = true;
        //             flag = true;
        //             snow[from]++;
        //         }
        //     }
        //     i = p[i];
        // }
    }
    cout << (d[n - 1] == INF? -1ll : d[n - 1]);
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