#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using ld = long double;
// #define int ll
#define double ld
const int MOD = 1e9 + 7;
const double eps = 1e-6;
const int SIGNES_AFTER_COMMA = 9;

bool winner(vector<int> &a, deque<pair<int, int>> &segments, bool turn) {
    if (segments.empty()) {
        return !turn;
    }
    bool w = !turn;
    for (int i = 0; i < (int)segments.size(); i++) {
        int l = segments.front().first;
        int r = segments.front().second;
        segments.pop_front();
        for (int k = 1; k <= 32; k++) {
            int newL = l;
            int added = 0;
            int del = 0;
            for (int j = l; j < r; j++) {
                if (a[j] == k) {
                    if (j != newL) {
                        segments.push_front({newL, j});
                        added++;
                    }
                    newL = j + 1;
                    del++;
                }
            }
            if (newL != r) {
                segments.push_front({newL, r});
                added++;
            }
            if (del) {
                auto x = winner(a, segments, !turn);
                if (x == turn) {
                    w = turn;
                }
            }
            for (int j = 0; j < added; j++) {
                segments.pop_front();
            }
        }
        segments.push_back({l, r});
    }
    return w;
}

void solve() {
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    vector<int> numE(n), numT(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        numE[i] = (i > 0? numE[i - 1] : 0);
        numT[i] = (i > 0? numT[i - 1] : 0);
        if (a[i] == 1) {
            if (i == 0 or a[i - 1] != 1) {
                numE[i]++;
            }
        } else if (a[i] == 2) {
            if (i == 0 or a[i - 1] != 2) {
                numT[i]++;
            }
        }
    }
    for (int i = 0; i < q; i++) {
        int l, r;
        cin >> l >> r;
        --l;
        deque<pair<int, int>> segs;
        segs.push_back({l, r});
        auto x = winner(a, segs, true);
        cout << x << '\n';
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