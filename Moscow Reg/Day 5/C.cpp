#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using ld = long double;
#define int ll
#define double ld
const int MOD = 1e9 + 7;
const double eps = 1e-6;
const int SIGNES_AFTER_COMMA = 9;

vector<int> tree;

void update(int i, int l, int r, int qi, int qv) {
    if (l > qi or r <= qi) {
        return;
    }
    if (r - l == 1) {
        tree[i] = max(tree[i], qv);
        return;
    }
    int m = (l + r) / 2;
    update(i * 2, l, m, qi, qv);
    update(i * 2 + 1, m, r, qi, qv);
    tree[i] = max(tree[i * 2], tree[i * 2 + 1]);
}

int get(int i, int l, int r, int ql, int qr) {
    if (ql <= l and r <= qr) {
        return tree[i];
    }
    if (l >= qr or r <= ql) {
        return -1;
    }
    int m = (l + r) / 2;
    return max(get(i * 2, l, m, ql, qr), get(i * 2 + 1, m, r, ql, qr));
}

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    vector<int> vals;
    for (auto &i : a) {
        cin >> i;
        vals.push_back(i);
    }
    sort(vals.begin(), vals.end());
    vals.erase(unique(vals.begin(), vals.end()), vals.end());
    vector<bool> used(vals.size(), false);
    {
        vector<int> precnt(vals.size() + 1, 0);
        for (auto &i : a) {
            i = lower_bound(vals.begin(), vals.end(), i) - vals.begin();
            precnt[i + 1]++;
        }
        for (int i = 1; i < (int)precnt.size(); i++) {
            precnt[i] += precnt[i - 1];
        }
        vector<int> cnt(vals.size(), 0);
        for (auto &i : a) {
            // i = precnt[i] + cnt[i]++;
        }
    }
    // tree.assign(4 * n, 0);
    vector<int> dpFromStart(n, 0);
    dpFromStart[0] = 1;
    for (int i = 1; i < n; i++) {

    }
    // update(1, 0, n, a[0], 1);
    // int maxDp = 1;
    // for (int i = 1; i < n; i++) {
    //     dp[i] = max(dp[i], get(1, 0, n, a[i] - 1, a[i] + 1) + 1);
    //     update(1, 0, n, a[i], dp[i]);
    //     maxDp = max(maxDp, dp[i]);
    // }
    cout << n << '\n';
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