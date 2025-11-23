#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using ld = long double;
#define int ll
#define double ld
const int MOD = 1e9 + 7;
const double eps = 1e-6;
const int SIGNES_AFTER_COMMA = 9;

int check(int &n, int &m, vector<int> a, int x) {
    int days = 0;
    int firstNotSolved = 0;
    while (firstNotSolved < n) {
        int solvedToday = 0;
        int cnt = 0;
        for (int i = firstNotSolved; i < n && cnt < m; i++, cnt++) {
            if (a[i] <= x) {
                x++;
                solvedToday++;
                swap(a[i], a[firstNotSolved]);
                firstNotSolved++;
            }
        }
        if (solvedToday == 0) return -1;
        days++;
    }
    return days;
}

void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    int maxH = 0;
    for (auto &i : a) {
        cin >> i;
        maxH = max(maxH, i);
    }
    int l = 0, r = maxH;
    int ans = 0;
    while (r - l > 1) {
        int x = (l + r) / 2;
        int d = check(n, m, a, x);
        if (d != -1) {
            r = x;
            ans = d;
        } else {
            l = x;
        }
    }
    cout << r << ' ' << ans << '\n';
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