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
    int n, p, k, d;
    cin >> n >> p >> k >> d;
    if (d > 1) {
        if (p - (d - 2) * (d - 1) / 2 > (k - 2)) {
            cout << p - (d - 2) * (d - 1) / 2 << '\n';
            for (int i = d - 2; i >= 0; i--) {
                cout << i << '\n';
            }
            for (int i = 0; i < n - d; i++) {
                cout << 0 << '\n';
            }
        } else {
            cout << "Wrong information" << '\n';
        }
    } else {
        // (p - (n - k) * x) / k
        // (p - x) % k == 0
        if (n == k) {
            if (p % k == 0) {
                for (int i = 0; i < n; i++) {
                    cout << p / k << '\n';
                }
            } else {
                cout << "Wrong information" << '\n';
            }
            return;
        }
        int wanted = p / k;
        int dop = (p - (wanted * k) + n - k - 1) / (n - k);
        int com = (p - (wanted * k)) / (n - k);
        int x = (p - (wanted * k)) % (n - k);
        if (wanted >= dop) {
            for (int i = 0; i < k; i++) {
                cout << wanted << '\n';
            }
            for (int i = 0; i < x; i++) {
                cout << dop << '\n';
            }
            for (int i = 0; i < n - k - x; i++) {
                cout << com << '\n';
            }
        } else {
            cout << "Wrong information" << '\n';
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