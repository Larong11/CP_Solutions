#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using ld = long double;
#define double ld
const int MOD = 1e9 + 7;
const double eps = 1e-6;
const int SIGNES_AFTER_COMMA = 9;


void solve() {
    int n, m;
    cin >> n >> m;

    multiset<int> sell[4], buy[4];
    set<pair<int, int>> s, b;
    // x + y, x - y, -x + y, -x - y
    // |x1 - x2| + |y1 - y2| =
    // x1 - x2 + y1 - y2 = (x1 + y1) - (x2 + y2)
    // x2 - x1 + y1 - y2 = (y1 - x1) - (y2 - x2)
    // x1 - x2 + y2 - y1 = (x1 - y1) - (x2 - y2)
    // x2 - x1 + y2 - y1 = (-x1 - y1) - (-x2 - y2)
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        sell[0].insert(x + y);
        sell[1].insert(x - y);
        sell[2].insert(-x + y);
        sell[3].insert(-x - y);
        s.insert({x, y});
    }
    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        buy[0].insert(x + y);
        buy[1].insert(x - y);
        buy[2].insert(-x + y);
        buy[3].insert(-x - y);
        b.insert({x, y});
    }
    int q;
    cin >> q;
    while (q--) {
        int t, x, y;
        cin >> t >> x >> y;
        if (t == 1) {
            auto z = s.find({x, y});
            if (z != s.end()) {
                s.erase(z);
                sell[0].erase(sell[0].find({x + y}));
                sell[1].erase(sell[1].find({x - y}));
                sell[2].erase(sell[2].find({-x + y}));
                sell[3].erase(sell[3].find({-x - y}));
            } else {
                sell[0].insert(x + y);
                sell[1].insert(x - y);
                sell[2].insert(-x + y);
                sell[3].insert(-x - y);
                s.insert({x, y});
            }
        } else {
            auto z = b.find({x, y});
            if (z != b.end()) {
                b.erase(z);
                buy[0].erase(buy[0].find({x + y}));
                buy[1].erase(buy[1].find({x - y}));
                buy[2].erase(buy[2].find({-x + y}));
                buy[3].erase(buy[3].find({-x - y}));
            } else {
                buy[0].insert(x + y);
                buy[1].insert(x - y);
                buy[2].insert(-x + y);
                buy[3].insert(-x - y);
                b.insert({x, y});
            }
        }
        if (b.empty() or s.empty()) {
            cout << "KAPUT" << '\n';
        } else {
            ll ans = 0;
            for (int k = 0; k < 4; k++) {
                ll max0 = *buy[k].rbegin();
                ll min0 = *buy[k].begin();
                ll max1 = *sell[k].rbegin();
                ll min1 = *sell[k].begin();
                ans = max(ans, max(max0 - min1, max1 - min0));
            }
            cout << ans << '\n';
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