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
    vector<int> a(n);
    for (auto &i : a) {
        cin >> i;
    }
    queue<int> maximums;
    int l = 0, r = 0;
    int ans = 0;
    while (r < a.size()) {
        if (a[r] > m) {
            if (r == l) {
                r++;
                l++;
                continue;
            }
            l++;
            while (!maximums.empty() and maximums.front() < l) {
                maximums.pop();
            }
            if (maximums.empty()) {
                l = r;
            } else {
                ans += r - maximums.front();
            }
        } else  {
            if (a[r] == m) {
                maximums.push(r);
            }
            r++;
            if (!maximums.empty()) {
                ans++;
            }
        }
    }
    while (l < a.size()) {
        l++;
        while (!maximums.empty() and maximums.front() < l) {
            maximums.pop();
        }
        if (maximums.empty()) {
            break;
        }
        ans += r - maximums.front();
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