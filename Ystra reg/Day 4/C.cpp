#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using ld = long double;
#define int ll
#define double ld
const int MOD = 1e9 + 7;
const double eps = 1e-6;
const int SIGNES_AFTER_COMMA = 9;

map<string, int> anses;

void solve01(int &n, string &s) {
    for (int i = 0; i < n - 1; i++) {
        if (s[i] == 'A' and s[i + 1] == 'B') {
            cout << 1 << '\n';
            return;
        }
        if (s[i] == 'B' and s[i + 1] == 'C') {
            cout << 1 << '\n';
            return;
        }
        if (s[i] == 'C' and s[i + 1] == 'A') {
            cout << 1 << '\n';
            return;
        }
    }
    cout << 0 << '\n';
    return;
}

bool solveABC(int &n, string &s) {
    int A = 0, B = 0, C = 0;
    for (auto &c : s) {
        if (c == 'A') {
            if (B != 0 or C != 0) {
                return false;
            }
            A++;
        } else if (c == 'B') {
            if (C != 0) {
                return false;
            }
            B++;
        } else {
            C++;
        }
    }
    anses[s] = max(A * B,B * C);
    cout << max(A * B,B * C) << '\n';
    return true;
}

bool solveAB(int &n, string &s) {
    int ans = 0;
    int A = 0;
    for (int i = 0; i < n; i++) {
        if (s[i] == 'A') {
            A++;
        } else if (s[i] == 'B') {
            ans += A;
        } else {
            return false;
        }
    }
    cout << ans << '\n';
    return true;
}

void SOLVE(int &n, string &s) {
    vector<vector<vector<int>>> dp(n, vector<vector<int>>(3, vector<int>(n + 1, -1)));
    dp[0][0][0] = 0;
    dp[0][1][0] = 0;
    dp[0][2][0] = 0;
    if (s[0] == 'A') {
        dp[0][0][1] = 0;
    } else if (s[0] == 'B') {
        dp[0][1][1] = 0;
    } else {
        dp[0][2][1] = 0;
    }
    int ans = 0;
    for (int i = 1; i < n; i++) {
        if (s[i] == 'A') {
            for (int j = 0; j < n; j++) {
                dp[i][0][j + 1] = max(dp[i][0][j + 1], dp[i - 1][0][j]);
            }
            for (int j = 1; j <= n; j++) {
                if (dp[i - 1][2][j] != -1) {
                    dp[i][2][j] = max(dp[i][2][j], dp[i - 1][2][j] + j);
                }
            }
        }
        if (s[i] == 'B') {
            for (int j = 0; j < n; j++) {
                dp[i][1][j + 1] = max(dp[i][1][j + 1], dp[i - 1][1][j]);
            }
            for (int j = 1; j <= n; j++) {
                if (dp[i - 1][0][j] != -1) {
                    dp[i][0][j] = max(dp[i][0][j], dp[i - 1][0][j] + j);
                }
            }
        }
        if (s[i] == 'C') {
            dp[i][2][1] = ans;
            for (int j = 0; j < n; j++) {
                dp[i][2][j + 1] = max(dp[i][2][j + 1], dp[i - 1][2][j]);
            }
            for (int j = 1; j <= n; j++) {
                if (dp[i - 1][1][j] != -1) {
                    dp[i][1][j] = max(dp[i][1][j], dp[i - 1][1][j] + j);
                }
            }
        }
        for (int j = 0; j <= n; j++) {
            dp[i][0][0] = max(dp[i][0][0], max(dp[i][1][j], dp[i][2][j]));
            dp[i][1][0] = max(dp[i][1][0], max(dp[i][0][j], dp[i][2][j]));
            dp[i][2][0] = max(dp[i][2][0], max(dp[i][1][j], dp[i][0][j]));

            ans = max(ans, max(dp[i][0][j], max(dp[i][1][j], dp[i][2][j])));
        }
    }
    cout << ans << '\n';
}

void solve() {
    int n;
    cin >> n;
    string s;
    cin >> s;
    anses.clear();
    if (n <= 2000) {
        SOLVE(n, s);
    } else {
        if (!solveABC(n, s)) {
            if (!solveAB(n, s)) {
                solve01(n, s);
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
#endif
    cin >> q;
    while (q--) {
        solve();
    }
}