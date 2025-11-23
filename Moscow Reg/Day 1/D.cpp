#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using ld = long double;
#define int ll
#define double ld
const int MOD = 1e9 + 7;
const double eps = 1e-6;
const int SIGNES_AFTER_COMMA = 9;

vector<int> ans;

void gen(int i, vector<vector<int>> &routes, vector<int> &edges, vector<vector<int>> &g, vector<int> &updown) {
    if (i == routes.size()) {
        int k = 0;
        for (auto &e : edges) {
            e = 0;
        }
        if (updown[0] == 1 and updown[1] == -1 and updown[2] == 1 and updown[3] == -1 and updown[4] == -1) {
            cout << "HELLO";
        }
        for (auto &rout : routes) {
            for (int j = 0; j < rout.size() - 1; j++) {
                int e = g[rout[j]][rout[j + 1]];
                if (e > 0) {
                    e--;
                    if (edges[e] == 0) {
                        edges[e] = updown[k];
                    } else if (edges[e] != updown[k]) {
                        return;
                    }
                } else {
                    e = -e - 1;
                    if (edges[e] == 0) {
                        edges[e] = -updown[k];
                    } else if (edges[e] == updown[k]) {
                        return;
                    }
                }
            }
            k++;
        }
        ans = updown;
        return;
    }
    if (!ans.empty()) {
        return;
    }
    updown[i] = 1;
    gen(i + 1, routes, edges, g, updown);
    updown[i] = -1;
    gen(i + 1, routes, edges, g, updown);
}

void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> edges;
    vector<vector<int>> g(n, vector<int>(n, -1));
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        edges.push_back(0);
        v--; u--;
        g[u][v] = (i + 1);
        g[v][u] = -(i + 1);
    }
    int k;
    cin >> k;
    vector<vector<int>> b(k);
    for (auto &vec : b) {
        int x;
        cin >> x;
        while (x != 0) {
            vec.push_back(x - 1);
            cin >> x;
        }
    }
    // sort(b.begin(), b.end(), [](vector<int> &a, vector<int> &b) {
    //     return a.size() > b.size();
    // });
    vector<int> updown(k, -1);
    ans = vector<int>();
    gen(0, b, edges, g, updown);
    if (ans.empty()) {
       cout << -1 << '\n';
    } else {
        vector<int> a(n, 0);
        int k = 0;
        for (auto &rout : b) {
            if (a[rout[0]] == 0) {
                if (ans[k] == 1) {
                    a[rout[0]] = 1;
                } else {
                    a[rout[0]] = n;
                }
            }
            // for (int i = 1; i < rout.size(); i++) {
            //     if (ans[k] == 1) {
            //         if (a[rout[i]] <= a[rout[i - 1]]) {
            //             a[rout[i]] = a[rout[i - 1]] + 1;
            //         }
            //     } else {
            //         if (a[rout[i]] >= a[rout[i - 1]]) {
            //             a[rout[i]] = a[rout[i - 1]] - 1;
            //         }
            //     }
            // }
            k++;
        }
        for (auto &i : a) {
            cout << i << ' ';
        }
    }
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