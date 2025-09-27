#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using ld = long double;
#define int ll
// #define double ld
const int MOD = 1e9 + 7;
const double eps = 1e-6;
const int SIGNES_AFTER_COMMA = 10;

int iter = 0;

int n;

void get(int i, double &curLen, double &sumMin, vector<int> &cur, vector<bool> &used, vector<vector<pair<double, int>>> &g, vector<double> &mins, vector<int> &ans, double &lenAns) {
    if (cur.size() == used.size() - 1) {
        if (curLen + g[i].back().first < lenAns) {
            lenAns = curLen + g[i].back().first;
            ans = cur;
        }
        return;
    }
    if (n == 20) {
        if (iter > 1e7) {
            return;
        }
    } else {
        if (iter > 125e5) {
            return;
        }
    }
    iter++;
    used[i] = true;
    for (int j = 1; j < g[i].size() - 1; j++) {
        if (!used[g[i][j].second] and curLen + g[i][j].first + sumMin - mins[i] < lenAns) {
            cur.push_back(g[i][j].second + 1);
            curLen += g[i][j].first;
            sumMin -= mins[i];
            get(g[i][j].second, curLen, sumMin, cur, used, g, mins, ans, lenAns);
            curLen -= g[i][j].first;
            sumMin += mins[i];
            cur.pop_back();
        }
    }
    used[i] = false;
}

void solve() {
    cin >> n;
    vector<pair<double, double>> p(n);
    for (auto &i : p) {
        cin >> i.first >> i.second;
    }
    vector<vector<pair<double, int>>> g(n, vector<pair<double, int>>(n));
    vector<double> mins(n, 1e18);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++) {
            double dx = (p[i].first - p[j].first);
            double dy = (p[i].second - p[j].second);
            double dst = sqrt(dx * dx + dy * dy);
            g[i][j] = {dst, j};
            g[j][i] = {dst, i};
            mins[i] = min(mins[i], dst);
            mins[j] = min(mins[j], dst);
        }
        g[i][i] = {0, i};
    }
    for (auto &vec : g) {
        auto ret = vec[0];
        sort(vec.begin(), vec.end());
        vec.push_back(ret);
    }
    double sumMin = 0;
    for (int i = 0; i < n; i++) {
        sumMin += mins[i];
    }
    vector<int> ans;
    vector<int> cur;
    vector<bool> used(n, false);
    double lenAns = 2e18;
    double curLen = 0;
    get(0, curLen, sumMin, cur, used, g, mins, ans, lenAns);
    cout << lenAns << '\n';
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