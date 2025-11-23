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
    vector<int> a(n);
    vector<int> vals;
    for (auto &i : a) {
        cin >> i;
        vals.push_back(i);
    }
    sort(vals.begin(), vals.end());
    vals.erase(unique(vals.begin(), vals.end()), vals.end());
    vector<int> cnt(vals.size(), 0);
    if (k > vals.size()) {
        cout << 0 << '\n';
        return;
    }
    int ans = 0;
    for (auto &i : a) {
        i = lower_bound(vals.begin(), vals.end(), i) - vals.begin();
        cnt[i]++;
    }
    for (auto &i : cnt) {
        cout << i << ' ';
    }
    cout << '\n';
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