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
    vector<pair<int, int>> a(n);
    vector<int> breeds;
    for (auto &i : a) {
        cin >> i.first >> i.second;
        breeds.emplace_back(i.second);
    }
    sort(a.begin(), a.end());
    sort(breeds.begin(), breeds.end());
    breeds.erase(unique(breeds.begin(), breeds.end()), breeds.end());
    for (auto &i : a) {
        i.second = lower_bound(breeds.begin(), breeds.end(), i.second) - breeds.begin();
    }
    int l = 0, r = 0;
    vector<int> cnt(breeds.size(), 0);
    int notUsed = (int)breeds.size();
    int ans = 2e9;
    while (l != n) {
        while (notUsed and r != n) {
            if (cnt[a[r++].second]++ == 0) {
                notUsed--;
            }
        }
        if (notUsed == 0) {
            ans = min(ans, a[r - 1].first - a[l].first);
        }
        if (--cnt[a[l++].second] == 0) {
            notUsed++;
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