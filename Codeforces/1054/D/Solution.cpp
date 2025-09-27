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
    string s;
    cin >> s;
    int ansA = 0, ansB = 0;
    int sumA = 0, sumB = 0;
    for (char &c : s) {
        if (c == 'a') {
            sumA++;
        } else {
            sumB++;
        }
    }
    int lastA = -1, lastB = -1;
    int cntA = 0, cntB = 0;
    for (int i = 0; i < n; i++) {
        if (s[i] == 'a') {
            if (lastA != -1) {
                ansA += (i - lastA - 1) * min(cntA, sumA - cntA);
            } 
            lastA = i;
            cntA++;
        } else {
            if (lastB != -1) {
                ansB += (i - lastB - 1) * min(cntB, sumB - cntB);
            } 
            lastB = i;
            cntB++;
        }
    }
    cout << min(ansB, ansA) << '\n';
}


signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
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