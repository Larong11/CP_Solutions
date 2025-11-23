#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using ld = long double;
// #define int ll
#define double ld
const int MOD = 1e9 + 7;
const double eps = 1e-6;
const int SIGNES_AFTER_COMMA = 9;

void solve() {
    int n, k;
    cin >> n >> k;
    int ans = 0;
    vector<int> a(n);
    for (auto &i : a) {
        cin >> i;
        --i;
    }
    if (k == 1) {
        cout << n * (n + 1ll) / 2ll << '\n';
    } else {
        vector<int> cnt(k);
        int ans = 0;
        for (int i = 0; i < n; i++) {
            cnt.assign(k, 0);
            int maxim = 0;
            for (int j = i; j < n; j++) {
                cnt[a[j]]++;
                if (cnt[a[j]] > maxim) {
                    maxim = cnt[a[j]];
                }
                if (maxim > (j - i + 1) / 2) {
                    ans++;
                }
            }
        }
        cout << ans << '\n';
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