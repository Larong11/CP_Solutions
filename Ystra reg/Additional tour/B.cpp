#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using ld = long double;
#define int ll
#define double ld
const int MOD = 1e9 + 7;
const double eps = 1e-6;
const int SIGNES_AFTER_COMMA = 9;

void solve() {
    int m;
    cin >> m;
    vector<string> names;
    vector<pair<string, string>> fromTo;
    for (int i = 0; i < m; i++) {
        string from, x, to;
        cin >> from >> x >> to;
        names.push_back(from);
        names.push_back(to);
        fromTo.emplace_back(from, to);
    }
    string startName, endName;
    cin >> startName >> endName;
    names.push_back(startName);
    names.push_back(endName);
    sort(names.begin(), names.end());
    names.erase(unique(names.begin(), names.end()), names.end());
    vector<vector<int>> g(names.size());
    for (auto &[from, to] : fromTo) {
        int f = lower_bound(names.begin(), names.end(), from) - names.begin();
        int t = lower_bound(names.begin(), names.end(), to) - names.begin();
        g[f].push_back(t);
    }
    int start = lower_bound(names.begin(), names.end(), startName) - names.begin(),
        end = lower_bound(names.begin(), names.end(), endName) - names.begin();
    vector<int> d(names.size(), -1);
    queue<pair<int, int>> q;
    q.push({start, 0});
    while (!q.empty()) {
        auto [u, w] = q.front();
        q.pop();
        if (d[u] != -1) {
            continue;
        }
        d[u] = w;
        for (auto &v : g[u]) {
            q.push({v, w + 1});
        }
    }
    cout << d[end] << '\n';
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