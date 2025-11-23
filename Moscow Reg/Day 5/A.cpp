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
    int n, k, m;
    cin >> n >> k;
    vector<int> a(n);
    vector<int> nextIdx(n);
    int upd = 0;
    {
        vector<int> vals;
        for (auto &i : a) {
            cin >> i;
            vals.push_back(i);
        }
        sort(vals.begin(), vals.end());
        vals.erase(unique(vals.begin(), vals.end()), vals.end());
        for (int i = 0; i < n; i++) {
            a[i] = lower_bound(vals.begin(), vals.end(), a[i]) - vals.begin();
        }
        vector<int> next(vals.size(), n + 1);
        for (int i = n - 1; i >= 0; i--) {
            nextIdx[i] = next[a[i]];
            next[a[i]] = i;
        }
        m = vals.size();
    }
    if (k > m) {
        cout << 0 << '\n';
        return;
    }
    {
        vector<bool> used(m, false);
        int cnt = m;
        for (int i = 0; i < n and cnt; i++) {
            if (!used[a[i]]) {
                upd = i;
                cnt--;
                used[a[i]] = true;
            }
        }
    }
    int newUpd = 0;
    int ans = 0;
    for (int i = 0; i < n; i++) {
        if (upd >= n) {
            break;
        }
        if (i == upd) {
            ans++;
            upd = newUpd;
        }
        newUpd = max(newUpd, nextIdx[i]);
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