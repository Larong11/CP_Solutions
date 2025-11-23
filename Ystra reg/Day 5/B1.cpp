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
    int n, m;
    cin >> n >> m;
    vector<vector<int>> a(n, vector<int>(m));
    bool flag = true;
    for (auto &vec : a) {
        for (auto &i : vec) {
            cin >> i;
            if (i != 0) {
                flag = false;
            }
        }
    }
    if (flag) {
        cout << "YES" << '\n';
        cout << 0 << '\n';
        return;
    }

    if (n % 3 == 0) {
        cout << "YES" << '\n';
        cout << m * n / 3 << '\n';
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j += 3) {
                cout << i + 1 << ' ' << j + 1 << ' ' << i + 1 << ' ' << j + 3 << ' ' << -a[j][i] << '\n';
            }
        }
    } else if (m % 3 == 0) {
        cout << "YES" << '\n';
        cout << m * n / 3 << '\n';
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j += 3) {
                cout << j + 1 << ' ' << i + 1 << ' ' << j + 3 << ' ' << i + 1 << ' ' << -a[i][j] << '\n';
            }
        }
    } else {
        cout << "NO" << '\n';
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
    }
}