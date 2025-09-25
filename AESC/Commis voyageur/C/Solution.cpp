#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using ld = long double;
#define int ll
// #define double ld
const int MOD = 1e9 + 7;
const double eps = 1e-6;
const int SIGNES_AFTER_COMMA = 10;

void get(int i, double curLen, int sumMin, vector<int> &cur, vector<bool> &used, vector<vector<double>> &g, vector<double> &mins, vector<int> &ans, double &lenAns) {
    if (cur.size() == used.size() - 1) {
        if (curLen + g[i][0] < lenAns) {
            lenAns = curLen + g[i][0];
            ans = cur;
        }
        return;
    }
    used[i] = true;
    for (int j = 0; j < g[i].size(); j++) {
        if (!used[j] and curLen + g[i][j] + sumMin - mins[i] < lenAns) {
            cur.push_back(j + 1);
            get(j, curLen + g[i][j], sumMin - mins[i], cur, used, g, mins, ans, lenAns);
            cur.pop_back();
        }
    }
    used[i] = false;
}

void solve() {
    int n;
    cin >> n;
    vector<pair<double, double>> p(n);
    for (auto &i : p) {
        cin >> i.first >> i.second;
    }
    vector<vector<double>> g(n, vector<double>(n));
    vector<double> mins(n, 1e18);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++) {
            double dx = (p[i].first - p[j].first);
            double dy = (p[i].second - p[j].second);
            double dst = sqrt(dx * dx + dy * dy);
            g[i][j] = dst;
            g[j][i] = dst;
            mins[i] = min(mins[i], dst);
            mins[j] = min(mins[j], dst);
        }
    }
    double sumMin = 0;
    for (int i = 0; i < n; i++) {
        sumMin += mins[i];
    }
    vector<int> ans;
    vector<int> cur;
    vector<bool> used(n, false);
    double len = 2e18;
    get(0, 0, sumMin, cur, used, g, mins, ans, len);
    cout << len << '\n';
    for (auto &i : ans) {
        cout << i << ' ';
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