#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using ld = long double;
#define double ld
const int MOD = 1e9 + 7;
const double eps = 1e-6;
const int SIGNES_AFTER_COMMA = 9;

const int INF = 1e9;

struct node {
    bool none, up, down;
};

void solve() {
    int n;
    cin >> n;
    vector<int> y0, y1, xvals;
    vector<pair<int, int>> xs;
    for (int i = 0; i < 2 * n; i++) {
        int x, y;
        cin >> x >> y;
        xs.emplace_back(x, y);
        xvals.push_back(x);
    }
    sort(xs.begin(), xs.end());
    sort(xvals.begin(), xvals.end());
    xvals.erase(unique(xvals.begin(), xvals.end()), xvals.end());
    vector<pair<int, int>> cntx(xvals.size());
    for (auto [x, y] : xs) {
        auto idx = lower_bound(xvals.begin(), xvals.end(), x) - xvals.begin();
        cntx[idx].first += y == 0;
        cntx[idx].second += y == 1;
    }
    int ans = 0;
    for (int i = 0; i < 2 * n; i += 2) {
        ans = max(ans, xs[i + 1].first - xs[i].first);
    }
    vector<node> dp(xvals.size(), {false, false, false});
    if ((cntx[0].first & 1) == (cntx[0].second & 1)) {
        if (cntx[0].first & 1) {
            if (ans >= 1) {
                dp[0].none = true;
            }
        } else {
            dp[0].none = true;
        }
    } else {
        if (cntx[0].first == 0) {
            dp[0].up = true;
        } else if(cntx[0].second == 0) {
            dp[0].down = true;
        } else {
            dp[0].up = true;
            dp[0].down = true;
        }
    }
    for (int prev_pref = 0; prev_pref < (int)xvals.size() - 1; prev_pref++) {
        int pref = prev_pref + 1;
        int cnt0 = cntx[pref].first;
        int cnt1 = cntx[pref].second;

        bool dSame = xvals[pref] - xvals[prev_pref] <= ans;
        bool dDif = xvals[pref] - xvals[prev_pref] + 1 <= ans;

        // dp[prev_pref].none ->
        if (dp[prev_pref].none) {
            if ((cnt0 & 1) == (cnt1 & 1)) {
                dp[pref].none = ((cnt0 & 1) == 0 or ans >= 1);
            } else {
                if (cnt0 == 0) {
                    dp[pref].up = true;
                } else if (cnt1 == 0) {
                    dp[pref].down = true;
                } else {
                    dp[pref].up = true;
                    dp[pref].down = true;
                }
            }
        }

        // dp[prev_pref].down ->
        if (dp[prev_pref].down) {
            if (cnt0 == 0) {
                if (cnt1 & 1) {
                    dp[pref].none |= dDif;
                } else {
                    dp[pref].up |= dDif;
                }
            } else if (cnt1 == 0) {
                if (cnt0 & 1) {
                    dp[pref].none |= dSame;
                } else {
                    dp[pref].down |= dSame;
                }
            } else {
                if (dSame) {
                    if ((cnt1 & 1) == ((cnt0 - 1) & 1)) {
                        dp[pref].none = true;
                    } else {
                        dp[pref].up = true;
                        if (cnt0 - 1 > 0 and (cnt1 & 1) == ((cnt0 - 2) & 1)) {
                            dp[pref].down = true;
                        }
                    }
                }
                if (dDif) {
                    if (((cnt1 - 1) & 1) == (cnt0 & 1)) {
                        dp[pref].none = true;
                    } else {
                        dp[pref].down = true;
                        if (cnt1 - 1 > 0 and (cnt0 & 1) == ((cnt1 - 2) & 1)) {
                            dp[pref].up = true;
                        }
                    }
                }
            }
        }


        // dp[prev_pref].up ->
        if (dp[prev_pref].up) {
            if (cnt0 == 0) {
                if (cnt1 & 1) {
                    dp[pref].none |= dSame;
                } else {
                    dp[pref].up |= dSame;
                }
            } else if (cnt1 == 0) {
                if (cnt0 & 1) {
                    dp[pref].none |= dDif;
                } else {
                    dp[pref].down |= dDif;
                }
            } else {
                if (dSame) {
                    if (((cnt1 - 1) & 1) == (cnt0 & 1)) {
                        dp[pref].none = true;
                    } else {
                        dp[pref].down = true;
                        if (cnt1 - 1 > 0 and (cnt0 & 1) == ((cnt1 - 2) & 1)) {
                            dp[pref].up = true;
                        }
                    }
                }
                if (dDif) {
                    if ((cnt1 & 1) == ((cnt0 - 1) & 1)) {
                        dp[pref].none = true;
                    } else {
                        if (cnt0 - 1 > 0 and (cnt1 & 1) == ((cnt0 - 2) & 1)) {
                            dp[pref].down = true;
                        }
                        dp[pref].up = true;
                    }
                }
            }
        }
    }
    if (dp[(int)xvals.size() - 1].none) {
        cout << ans << '\n';
    } else {
        cout << ans + 1 << '\n';
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