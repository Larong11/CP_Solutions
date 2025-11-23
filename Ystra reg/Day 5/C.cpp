#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using ld = long double;
#define int ll
#define double ld
const int MOD = 1e9 + 7;
const double eps = 1e-6;
const int SIGNES_AFTER_COMMA = 9;

const ll LINF = 1e18;


void solve() {
    int n, k, m;
    cin >> n >> k >> m;
    vector<int> bluda(n);
    int sum =0;
    for (auto &i : bluda) {
        cin >> i;
        sum += i;
    }
    vector<int> cooks(m);
    for (auto &i : cooks) {
        cin >> i;
    }
    vector<vector<int>> D(1, vector<int>(m, 0));
    int w = 1;
    while (true) {
        D.push_back(vector<int>(m + 1, 0));
        int mx = 0;
        for (int j = 1; j <= m; j++) {
            D[w][j] = w - min(cooks[j - 1], n) >= 0? D[w - min(cooks[j - 1], n)][j - 1] : D[w][j - 1];
            mx = max(mx, D[w][j]);
        }
        if (w >= sum and mx >= n * k) {
            break;
        }
    }
    cout << w - sum << '\n';
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