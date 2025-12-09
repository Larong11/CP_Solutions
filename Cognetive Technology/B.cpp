#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using ld = long double;
#define int ll
#define double ld
const int MOD = 1e9 + 7;
const double eps = 1e-6;
const int SIGNES_AFTER_COMMA = 9;

bool can(int h, int &n, int &a, int &M, vector<int> &b) {
    double minus = 0;
    for (int i = 0; i < n; i++) {
        int xD = max(0ll, b[i] - h);
        int d = b[i] - xD;
        // 1 * t + (a * t^2)/2 = d
        // a/2 * t^2 + t - d = 0
        double D = 1.0 + 2.0 * a * d;
        double t = (-1.0 + sqrt(D)) / double(a);
        double V = (-1.0 + sqrt(D));

        minus += D;
    }
    return minus < double(M);
}

void solve() {
    int n, a, M;
    cin >> n >> a >> M;
    vector<int> b(n);
    for (auto &i : b) {
        cin >> i;
    }
    sort(b.begin(), b.end());
    int l = 1, r = b.back() + 1;
    while (r - l > 1) {
        int m = (l + r) / 2;
        if (can(m, n, a, M, b)) {
            l = m;
        } else {
            r = m;
        }
    }
    cout << l << '\n';
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