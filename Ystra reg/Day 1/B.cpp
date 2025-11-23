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
    int L, R;
    cin >> L >> R;
    vector<pair<int, int>> closed;
    for (int _ = 0; _ < R; _++) {
        int x;
        cin >> x;
        int leftSum = 0, rightSum = 0;
        vector<int> lengths(x);
        for (auto &i : lengths) {
            cin >> i;
            rightSum += i;
        }
        vector<pair<int, int>> curOpen;
        for (int i = 0; i <= x; i++) {
            curOpen.emplace_back(leftSum, 0);
            curOpen.emplace_back(L - rightSum, 1);
            if (i < x) {
                leftSum += lengths[i];
                rightSum -= lengths[i];
            }
        }
        sort(curOpen.begin(), curOpen.end());
        int prev = 0, open = 0;
        for (auto &[cur, b] : curOpen) {
            if (open == 0) {
                if (cur != 0) {
                    closed.emplace_back(prev, 0);
                    closed.emplace_back(cur, 1);
                }
            }
            if (b == 0) {
                open++;
            } else {
                open--;
            }
            prev = cur;
        }
    }
    int ans = 0;
    int open = 0, firstOpen = 0;
    sort(closed.begin(), closed.end());
    for (auto &[cur, b] : closed) {
        if (b == 0) {
            open++;
            if (open == 1) {
                firstOpen = cur;
            }
        } else {
            open--;
            if (open == 0) {
                ans += cur - firstOpen;
            }
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
// 4:22:10