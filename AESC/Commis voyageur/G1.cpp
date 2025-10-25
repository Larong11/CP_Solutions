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
    int N, K;
    cin >> N >> K;

    long long S = 1LL * N * (N + 1) / 2;
    if (S % K != 0) {
        cout << 0 << "\n";
        return;
    }

    int perGroup = N / K;
    int l = 1, r = N;

    vector<vector<int>> a(K);
    int sum = 0;
    for (int i = 0; i < K; i++) {
        for (int j = 0; j < perGroup / 2; j++) {
            a[i].push_back(l++);
            sum += a[i].back();
            a[i].push_back(r--);
            sum += a[i].back();
        }
        if (perGroup % 2 == 1) {
            a[i].push_back(l++);
            sum += a[i].back();
        }
        if (sum != S / K) {
            cout << 0 << '\n';
            return;
        }
        sum = 0;
    }   
    for (auto &vec : a) {
        for (auto &i : vec) {
            cout << i << ' ';
        }
        cout << '\n';
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