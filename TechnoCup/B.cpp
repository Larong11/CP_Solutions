#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using ld = long double;
// #define int ll
#define double ld
const ll MOD = 998244353;
const double eps = 1e-6;
const int SIGNES_AFTER_COMMA = 9;

void solve() {
    ll a, b, r, n;
    cin >> a >> b >> r >> n;
    vector<int> x;
    int p = 0;
    ll ans = 0;
    for (int i = 0; i < n; i++) {
        int curp = (a + b * p) % r;
        p = curp;
        x.push_back(p);
    }
    sort(x.begin(), x.end());
    ll cnt1 = 0, cnt2 = 0, cntcur = 0;
    int prev1 = -3, prev2 = -3, cur = -3;
    for (auto &i : x) {
        if (i != cur) {
            prev2 = prev1;
            cnt2 = cnt1;
            prev1 = cur;
            cnt1 = cntcur;
            cur = i;
            cntcur = 1;
        } else {
            cntcur++;
        }
        if (prev1 == cur - 2) {
            ans = (ans + cnt1) % MOD;
        }
        if (prev2 == cur - 2) {
            ans = (ans + cnt2) % MOD;
        }
    }
    cout << ans << '\n';
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