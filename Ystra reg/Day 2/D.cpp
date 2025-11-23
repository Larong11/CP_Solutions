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
    int n;
    cin >> n;
    vector<int> v(n);
    for (auto &i : v) {
        cin >> i;
    }
    vector<int> w(n);
    for (auto &i : w) {
        cin >> i;
    }
    int q;
    cin >> q;
    if (n <= 300) {
        vector<vector<int>> DP(n);
        for (int _ = 0; _ < q; _++) {
            int a, b;
            cin >> a >> b;
            if (DP[a].empty()) {
                vector<int> dp(n, 1e9);
                dp[a] = 0;
                int lastMin = 1 + a;
                for (int i = a; i < n; i++) {
                    for (int j = lastMin - i; i + j < n and j <= max(w[i], v[i]); j++) {
                        if (j <= v[i]) {
                            dp[i + j] = min(dp[i + j], dp[i] + 1);
                            lastMin = i + j;
                        } else {
                            dp[i + j] = min(dp[i + j], dp[i] + 2);
                        }
                    }
                }
                cout << dp[b] << '\n';
                DP[a] = dp;
            } else {
                cout << DP[a][b] << '\n';
            }
        }
    } else {
        vector<vector<pair<int, int>>> A(n);
        vector<int> AA;
        vector<int> ans(q);
        for (int _ = 0; _ < q; _++) {
            int a, b;
            cin >> a >> b;
            A[a].emplace_back(b, _);
            AA.push_back(a);
        }
        sort(AA.begin(), AA.end());
        for (auto &a : AA) {
            vector<int> dp(n, 1e9);
            dp[a] = 0;
            int lastMin = 1 + a;
            for (int i = a; i < n; i++) {
                for (int j = lastMin - i; i + j < n and j <= max(w[i], v[i]); j++) {
                    if (j <= v[i]) {
                        dp[i + j] = min(dp[i + j], dp[i] + 1);
                        lastMin = i + j;
                    } else {
                        dp[i + j] = min(dp[i + j], dp[i] + 2);
                    }
                }
            }
            for (auto &[b, i] : A[a]) {
                ans[i] = dp[b];
            }
        }
        for (auto &i : ans) {
            cout << i << '\n';
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