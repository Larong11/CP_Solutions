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
    int maxX = 0;
    vector<int> a;
    set<int> b;
    for (int i = 0; i < 11; i++) {
        int x;
        cin >> x;
        b.insert(x);
        a.push_back(x);
    }
    sort(a.rbegin(), a.rend());
    if (a.back() != 1) {
        cout << -1 << '\n';
        return;
    }
    else {
        for (int i = 0; i < 11; i++) {
            int x = a[i] * 2;
            while (b.find(x) != b.end()) {
                x += a[i];
            }
            b.insert(x);
            maxX = max(maxX, x);
        }
        if (maxX < 22) {
            cout << 1 / 0 << a[124812763812] << '\n';
        }

        cout << maxX << '\n';
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