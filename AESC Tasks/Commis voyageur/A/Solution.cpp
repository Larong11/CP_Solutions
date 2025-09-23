#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using ld = long double;
#define int ll
#define double ld
const int MOD = 1e9 + 7;
const double eps = 1e-6;
const int SIGNES_AFTER_COMMA = 9;

void get(int x, int y, vector<vector<int>> &ans, int i, int n, vector<vector<int>> &gAns) {
    if (!gAns.empty()) {
        return;
    }
    if (x < 0 or x >= ans.size() or y < 0 or y >= ans.size()) {
        return;
    }
    if (ans[y][x] != -1) {
        return;
    }
    ans[y][x] = i;
    if (i == n * n) {
        gAns = ans;
    }
    get(x + 1, y + 2, ans, i + 1, n, gAns);
    get(x + 2, y + 1, ans, i + 1, n, gAns);
    get(x + 2, y - 1, ans, i + 1, n, gAns);
    get(x + 1, y - 2, ans, i + 1, n, gAns);
    get(x - 1, y - 2, ans, i + 1, n, gAns);
    get(x - 2, y - 1, ans, i + 1, n, gAns);
    get(x - 2, y + 1, ans, i + 1, n, gAns);
    get(x - 1, y + 2, ans, i + 1, n, gAns);
    ans[y][x] = -1;
}

void solve() {
    int n;
    cin >> n;
    vector<vector<int>> cur(n, vector<int>(n, -1));
    vector<vector<int>> ans;
    get(0, 0, cur, 1, n, ans);
    if (ans.empty()) {
        cout << 0 << '\n';
    } else {
        cout << 1 << '\n';
        for (auto &vec : ans) {
            for (auto &i : vec) {
                cout << i << ' ';
            }
            cout << '\n';
        }
    }
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