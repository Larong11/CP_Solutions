#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using ld = long double;
#define double ld
const int MOD = 1e9 + 7;
const double eps = 1e-6;
const int SIGNES_AFTER_COMMA = 9;

const int K = 300;

void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    for (auto &i : a) {
        cin >> i;
    }
    vector<int> next(n), count(n), beforeDeath(n);
    for (int i = n - 1; i >= 0; i--) {
        if (i + a[i] >= n) {
            next[i] = -1;
            beforeDeath[i] = i;
            count[i] = 1;
        } else if (i / K == (a[i] + i) / K) {
            next[i] = next[a[i] + i];
            beforeDeath[i] = beforeDeath[a[i] + i];
            count[i] = count[a[i] + i] + 1;
        } else {
            next[i] = i + a[i];
            count[i] = 1;
        }
    }
    while (m--) {
        int c;
        cin >> c;
        if (c == 1) {
            int x;
            cin >> x;
            --x;
            int ans = 0;
            int prev = -1;
            while (x != -1) {
                ans += count[x];
                prev = beforeDeath[x];
                x = next[x];
            }
            cout << prev + 1 << ' ' << ans << '\n';
        } else {
            int idx, val;
            cin >> idx >> val;
            --idx;
            a[idx] = val;
            for (int i = idx; i >= int(idx / K) * K; i--) {
                if (i + a[i] >= n) {
                    next[i] = -1;
                    beforeDeath[i] = i;
                    count[i] = 1;
                } else if (i / K == (a[i] + i) / K) {
                    next[i] = next[a[i] + i];
                    beforeDeath[i] = beforeDeath[a[i] + i];
                    count[i] = count[a[i] + i] + 1;
                } else {
                    next[i] = i + a[i];
                    count[i] = 1;
                }
            }
        }
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