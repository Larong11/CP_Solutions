#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using ld = long double;

#define double ld
const int MOD = 1e9 + 7;
const double eps = 1e-6;
const int SIGNES_AFTER_COMMA = 9;

void solve() {
    string s, t;
    cin >> s >> t;
    if (s.size() > t.size()) {
        swap(s, t);
    }
    int ss = s.size();
    int ts = t.size();
    for (int i = 1; i <= ss; i++) {
        if (ss % i == 0 and ts % i == 0) {
            bool ok = true;
            for (int j = 0; ok and j < ss; j++) {
                if (s[j] != s[j - (int(j / i) * i)]) {
                    ok = false;
                }
            }
            for (int j = 0; ok and j < ts; j++) {
                if (t[j] != s[j - (int(j / i) * i)]) {
                    ok = false;
                }
            }
            if (ok) {
                for (int j = 0; j < i; j++) {
                    cout << s[j];
                }
                cout << '\n';
                return;
            }
        }
    }
    cout << "NO SIGNAL" << '\n';
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