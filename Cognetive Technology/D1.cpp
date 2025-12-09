#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using ld = long double;
#define int ll
#define double ld
const int MOD = 1e9 + 7;
const double eps = 1e-6;
const int SIGNES_AFTER_COMMA = 9;

struct points {
    multiset<int> a[4];
    void insert(int x, int y) {
        a[0].insert(x + y);
        a[1].insert(-x + y);
        a[2].insert(x - y);
        a[3].insert(-x - y);
    }
    bool empty() {
        return a[0].empty();
    }
    bool erase(int x, int y) {
        auto f0 = a[0].find(x + y);
        auto f1 = a[1].find(-x + y);
        auto f2 = a[2].find(x - y);
        auto f3 = a[3].find(-x - y);
        if (f0 != a[0].end() and f1 != a[1].end() and f2 != a[2].end() and f3 != a[3].end()) {
            a[0].erase(f0);
            a[1].erase(f1);
            a[2].erase(f2);
            a[3].erase(f3);
        } else {
            return false;
        }
        return true;
    }
    multiset<int> &operator[](int i) {
        return a[i];
    }
};

int dist(pair<int, int> a, pair<int, int> b) {
    return abs(a.first - b.first) + abs(a.second - b.second);
}

void solve() {
    int n, m;
    cin >> n >> m;
    set<pair<int, int>> a;
    set<pair<int, int>> b;
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        a.insert({x, y});
    }
    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        b.insert({x, y});
    }
    int q;
    cin >> q;
    while (q--) {
        int t, x, y;
        cin >> t >> x >> y;
        if (t == 1) {
            if (a.count({x, y})) {
                a.erase({x, y});
            } else {
                a.insert({x, y});
            }
        } else {
            if (b.count({x, y})) {
                b.erase({x, y});
            } else {
                b.insert({x, y});
            }
        }
        if (a.empty() or b.empty()) {
            cout << "KAPUT" << '\n';
            continue;
        }
        int ans = 0;
        for (auto &i : a) {
            for (auto &j : b) {
                ans = max(ans, dist(i, j));
            }
        }
        cout << ans << '\n';
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