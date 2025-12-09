#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using ld = long double;
#define int ll
#define double ld
const int MOD = 1e9 + 7;
const double eps = 1e-6;
const int SIGNES_AFTER_COMMA = 9;

struct node {
    int a, b, c;
};

void solve() {
    int n;
    cin >> n;
    string s;
    cin >> s;
    vector<pair<char, int>> a;
    for (auto &c : s) {
        if (a.empty() or a.back().first != c) {
            a.emplace_back(c, 1);
        } else {
            a.back().second++;
        }
    }
    vector<node> dp(a.size(), {-1, -1, -1});
    int m = (int)a.size();
    int lastA = m, lastB = m, lastC = m;
    vector<int> cntA(m, 0), cntB(m, 0), cntC(m, 0);

    node A = {0, 0, 0}, B = {0, 0, 0}, C = {0, 0, 0};
    if (s.back() == 'A') {
        dp.back().a = 0;
        A.b += a.back().second;
        A.c += a.back().second;
        lastA = m - 1;
    } else if (s.back() == 'B') {
        dp.back().b = 0;
        B.a += a.back().second;
        B.c += a.back().second;
        lastB = m - 1;
    } else {
        dp.back().c = 0;
        C.a += a.back().second;
        C.b += a.back().second;
        lastC = m - 1;
    }
    int swapCA = 0, swapAB = 0, swapBC = 0;

    for (int i = m - 2; i >= 0; i--) {

        if (a[i].first == 'A') {
            swapBC = 0;
            C.a = 0;
            B.a = 0;
            swapAB += a[i].second * B.c;

            A.b += a[i].second;
            A.c += a[i].second;
            lastA = i;


            dp[i].a = max({dp[i + 1].a, dp[i + 1].c});
            dp[i].c = -1;
            if (lastC == i + 1) {
                dp[i].b = -1;
            } else if (lastC == m) {
                dp[i].b = swapAB;
            } else if (a[lastC - 1].first == 'A') {
                dp[i].b = swapAB + max(dp[lastC].c, dp[lastC].a);
            } else if (a[lastC - 1].first == 'B') {
                dp[i].b = max(swapAB + max(dp[lastC].c, dp[lastC].a), swapAB - a[lastC - 1].second * A.c + dp[lastC - 1].c);
            }
        }
        if (a[i].first == 'B') {
            swapCA = 0;
            A.b = 0;
            C.b = 0;
            swapBC += a[i].second * C.a;

            B.a += a[i].second;
            B.c += a[i].second;
            lastB = i;

            dp[i].b = max({dp[i + 1].a, dp[i + 1].b});
            dp[i].a = -1;
            if (lastA == i + 1) {
                dp[i].c = -1;
            } else if (lastA == m) {
                dp[i].c = swapBC;
            } else if (a[lastA - 1].first == 'B') {
                dp[i].c = swapBC + max(dp[lastA].a, dp[lastA].b);
            } else if (a[lastA - 1].first == 'C') {
                dp[i].c = max(swapBC + max(dp[lastA].a, dp[lastA].b), swapBC - a[lastA - 1].second * B.a + dp[lastA - 1].a);
            }
        }
        if (a[i].first == 'C') {
            swapAB = 0;
            B.c = 0;
            A.c = 0;
            swapCA += a[i].second * A.b;

            C.a += a[i].second;
            C.b += a[i].second;
            lastC = i;


            dp[i].c = max({dp[i + 1].b, dp[i + 1].c});
            dp[i].b = -1;
            if (lastB == i + 1) {
                dp[i].a = -1;
            } else if (lastB == m) {
                dp[i].a = swapCA;
            } else if (a[lastB - 1].first == 'C') {
                dp[i].a = swapCA + max(dp[lastB].b, dp[lastB].c);
            } else if (a[lastB - 1].first == 'A') {
                dp[i].a = max(swapCA + max(dp[lastB].b, dp[lastB].c), swapCA - a[lastB - 1].second * C.b + dp[lastB - 1].b);
            }
        }
    }
    cout << max({dp[0].a, dp[0].b, dp[0].c, 0ll}) << '\n';
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