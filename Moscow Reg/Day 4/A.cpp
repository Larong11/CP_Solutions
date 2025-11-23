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
    int n;
    cin >> n;
    int sum = 0;
    vector<pair<int, int>> a;
    vector<pair<int, int>> b;
    for (int i = 0; i < n; i++) {
        int x, y, c;
        cin >> c >> x >> y;
        sum += c;
        a.emplace_back(x - c, i);
        b.emplace_back(y - c, i);
    }
    sort(a.rbegin(), a.rend());
    sort(b.rbegin(), b.rend());
    int f = sum + b[0].first + (b[0].second == a[0].second? a[1].first : a[0].first);
    int s = sum + a[0].first + (a[0].second == b[0].second? b[1].first : b[0].first);
    if (f > s) {
        cout << f << '\n';
        cout << (b[0].second == a[0].second? a[1].second : a[0].second) + 1 << ' ' << b[0].second + 1 << '\n';
    } else {
        cout << s << '\n';
        cout << a[0].second + 1 << ' ' << (a[0].second == b[0].second? b[1].second : b[0].second) + 1 << '\n';
    }
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