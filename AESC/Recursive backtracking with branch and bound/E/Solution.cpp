#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using ld = long double;
#define int ll
#define double ld
const int MOD = 1e9 + 7;
const double eps = 1e-6;
const int SIGNES_AFTER_COMMA = 9;

void get(int i, int sum, int n, vector<int> &fib, vector<int> &suf, vector<int> &cur) {
    if (i == fib.size()) {
        if (sum == n) {
            bool start = false;
            for (auto &j : cur) {
                if (j == 1) {
                    start = true;
                }
                if (start) {
                    cout << j;
                }
            }
            cout << '\n';
        }
        return;
    }
    if (sum > n) {
        return;
    }
    if (sum + suf[i + 1] >= n) {
        cur.push_back(0);
        get(i + 1, sum, n, fib, suf, cur);
        cur.pop_back();
    }
    if (sum + fib[i] <= n) {
        cur.push_back(1);
        get(i + 1, sum + fib[i], n, fib, suf, cur);
        cur.pop_back();
    }
}

void solve() {
    int n;
    cin >> n;
    vector<int> fib = {1, 2};
    while (fib.back() < n) {
        fib.push_back(fib.back() + fib[fib.size() - 2]);
    }
    reverse(fib.begin(), fib.end());
    vector<int> suf(fib.size() + 1, 0);
    for (int i = fib.size() - 1; i >= 0; i--) {
        suf[i] = suf[i + 1] + fib[i];
    }
    vector<int> cur;
    get(0, 0, n, fib, suf, cur);
}


signed main() {
    int q = 1;
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    cin >> q;
#endif
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(SIGNES_AFTER_COMMA);
    while (q--) {
        solve();
        cout << '\n';
    }
}