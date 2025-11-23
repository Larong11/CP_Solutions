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
    vector<int> indexes(n + 1);
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        indexes[x] = i;
    }
    vector<int> diff(n + 1);
    int ans = 0;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        int d = indexes[x] - i;
        if (d < 0) {
            d += n;
        }
        diff[d]++;
        if (diff[d] > ans) {
            ans = diff[d];
        }
    }
    cout << ans << '\n';
    
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