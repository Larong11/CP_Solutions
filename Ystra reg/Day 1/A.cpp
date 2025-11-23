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
    int n, m;
    cin >> n >> m;
    vector<int> a(m, -1);
    vector<set<int>> cities(m);
    set<pair<int, int>> minim;
    for (int i = 0; i < n; i++) {
        int c;
        cin >> c;
        if (c == 2) {
            auto x = --minim.end();
            int val = x->first, idx = x->second;
            cout << val << '\n';
            cities[idx].erase(cities[idx].begin());
            a[idx] = *cities[idx].begin();
            minim.erase(x);
            minim.insert({a[idx], idx});
        } else {
            int T, val;
            cin >> T >> val;
            --T;
            cities[T].insert(val);
            if (a[T] != *cities[T].begin()) {
                if (a[T] != -1)
                    minim.erase({a[T], T});
                a[T] = *cities[T].begin();
                minim.insert({a[T], T});
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
    cin >> q;
#endif
    while (q--) {
        solve();
    }
}