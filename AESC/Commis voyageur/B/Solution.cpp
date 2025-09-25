#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using ld = long double;
#define int ll
#define double ld
const int MOD = 1e9 + 7;
const double eps = 1e-6;
const int SIGNES_AFTER_COMMA = 9;

void getAns(int i, int left, vector<bool> &used, vector<vector<int>> &g, int curAns, int &ans) {
    if (left == 0) {
        if (g[i][0] != 0) {
            ans = min(curAns + g[i][0], ans);
        }
        return;
    }
    used[i] = true;
    for (int j = 0; j < g[i].size(); j++) {
        if (!used[j] and g[i][j] != 0) {
            getAns(j, left - 1, used, g, curAns + g[i][j], ans);
        }
    }
    used[i] = false;
}

void solve() {
    int n;
    cin >> n;
    vector<vector<int>> g(n, vector<int>(n));
    for (auto &vec : g) {
        for (auto &i : vec) {
            cin >> i;
        }
    }
    vector<bool> used(n, false);
    int ans = 1e18;
    getAns(0, n - 1, used, g, 0, ans);
    if (n == 1) {
        cout << 0 << '\n';
        return;
    }
    cout << (ans == 1e18? -1 : ans) << '\n';
}   


signed main() {
    int q = 1;
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    cin >> q;
#endif
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(SIGNES_AFTER_COMMA);
    while (q--) {
        solve();
    }
}