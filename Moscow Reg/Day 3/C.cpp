#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using ld = long double;
// #define int ll
#define double ld
const int MOD = 1e9 + 7;
const double eps = 1e-6;
const int SIGNES_AFTER_COMMA = 9;

vector<int> dels(int x) {
    vector<int> res;
    for (int i = 1; i * i <= x; i++) {
        int y = x / i;
        if (y * i == x) {
            res.push_back(i);
            if (i != y) {
                res.push_back(y);
            }
        }
    }
    return res;
}

inline int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    int maxA = 0;
    for (auto &i : a) {
        cin >> i;
        maxA = max(maxA, i);
    }
    vector<int> cnt(maxA + 1, 0);
    for (auto &i : a) {
        cnt[i]++;
    }
    int ans = 0;
    for (int i = 1; i <= maxA; i++) {
        if (cnt[i] != 0) {
            vector<int> del = dels(i);
            for (auto &j : del) {
                int y = i ^ j;
                if (y >= (int)cnt.size() or y <= i) {
                    continue;
                }
                if (cnt[y] != 0) {
                    if (gcd(y, i) == j) {
                        ans += cnt[i] * cnt[y];
                    }
                }
            }
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