#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using ld = long double;
#define int ll
#define double ld
const int MOD = 1e9 + 7;
const double eps = 1e-6;
const int SIGNES_AFTER_COMMA = 9;

int get(int i, int n, vector<bool> used) {
    if (i == n) {
        return 1;
    }
    int ans = get(i + 1, n, used);
    bool can = true;
    used[i] = true;
    for (int j = 0; j < i; j++) {
        if (used[j]) { // j = (i + x) - n  || i = (j + x)
            if (used[i - j] or used[j + n - i]) {
                can = false;
            }
        }
    }
    if (can) {
        ans += get(i + 1, n, used);
    }
    used[i] = false;
    return ans;
}

void solve() {
    int n;
    cin >> n;
    vector<bool> used(n + 1, false);
    cout << get(1, n, used) << '\n';
}


signed main() {
    int q = 1;
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    cin >> q;
#endif
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(SIGNES_AFTER_COMMA);
    while (q--) {
        solve();
    }
}