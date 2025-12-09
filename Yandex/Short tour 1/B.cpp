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
    vector<vector<int>> a(5, vector<int>(n));
    for (auto &vec : a) {
        for (auto &i : vec) {
            cin >> i;
        }
    }
    vector<int> breeds(n);
    for (int i = 0; i < n; i++) {
        breeds[i] = a[0][i];
    }
    sort(breeds.begin(), breeds.end());
    for (auto &vec : a) {
        for (auto &i : vec) {
            i = lower_bound(breeds.begin(), breeds.end(), i) - breeds.begin();
        }
    }
    vector<vector<int>> ans(n, vector<int>(5));
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < n; j++) {
            ans[a[i][j]][i] = j;
        }
    }
    for (int i = 0; i < n; i++) {
        cout << breeds[i] << ": ";
        for (auto &j : ans[i]) {
            cout << j + 1 << ' ';
        }
        cout << '\n';
    }
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
        cout << '\n';
    }
}