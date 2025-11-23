#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using ld = long double;
#define int ll
#define double ld
const int MOD = 1e9 + 7;
const double eps = 1e-6;
const int SIGNES_AFTER_COMMA = 600;

void solve() {
    int n;
    cin >> n;
    vector<pair<int, int>> points(n);
    for (auto &[x, y]: points) {
        cin >> x >> y;
    }
    int area = 0;
    for (int i = 0; i < n; i++) {
        auto [x1, y1] = points[i];
        auto [x2, y2] = points[(i + 1) >= n? 0 : i + 1];
        area += (x2 - x1) * (y1 + y2);
    }
    if (area < 0) {
        area = -area;
    }
    cout << double(area) / 2.0 << '\n';
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