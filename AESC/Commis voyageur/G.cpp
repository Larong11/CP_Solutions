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
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    vector<int> sums(k);
    int targetSum = (n + 1) * n / 2;
    int dSum = ;
    for (int i = 0; i < n; i++) {
        a[i] = i + 1;
        sums[i / (n / k)] += a[i];
    }
    for (auto &i : sums) {
        dsum
    }
    cout << '\n';
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