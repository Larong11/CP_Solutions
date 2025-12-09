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
    string s;
    cin >> s;
    int q;
    cin >> q;
    int n = s.size();

    vector<int> pref(n + 1, 0);
    for (int i = 0; i < n; ++i) {
        pref[i + 1] = (pref[i] * 2 + (s[i] - '0')) % 3;
    }

    auto get_sum = [&](int l, int r) {
        return ((pref[r] - pref[l] * ((r - l) % 2? 2 : 1)) % 3 + 3) % 3;
    };

    while (q--) {
        int l, r;
        cin >> l >> r;
        --l;

        int sum = get_sum(l, r);
        int ans = 0;
        cout << sum << '\n';
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