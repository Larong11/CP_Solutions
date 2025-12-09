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
    int n;
    cin >> n;
    vector<pair<int, int>> a(n);
    for (auto &i : a) {
        cin >> i.first >> i.second;
    }
    sort(a.begin(), a.end());
    int t = 0;
    bool UP = false, DOWN = false;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> times;
    priority_queue<pair<int, int>, vector<pair<int, int>>, less<pair<int, int>>> top;
    queue<pair<int, int>> bottom;
    for (int i = 0; i < n; i++) {
        bottom.push({a[i].first, i});
    }
    vector<bool> used(n, false);
    times.push({t + bottom.front().first, bottom.front().second});
    bottom.pop();
    UP = true;
    while (!times.empty()) {
        auto [curT, idx] = times.top();
        times.pop();
        if (used[idx]) {
            DOWN = false;
            t = curT;
        } else if (!used[idx]) {
            used[idx] = true;
            UP = false;
            top.push({a[idx].second, idx});
            t = curT;
        }
        if (!UP and !bottom.empty()) {
            UP = true;
            times.push({t + bottom.front().first, bottom.front().second});
            bottom.pop();
        }
        if (!DOWN and !top.empty()) {
            DOWN = true;
            times.push({t + top.top().first, top.top().second});
            top.pop();
        }
    }
    cout << t << '\n';
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