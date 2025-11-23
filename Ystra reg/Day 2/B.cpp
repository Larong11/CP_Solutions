#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using ld = long double;
#define int ll
#define double ld
const int MOD = 1e9 + 7;
const double eps = 1e-6;
const int SIGNES_AFTER_COMMA = 9;

const int nil = 1e9;

void buildMin(int tree[], vector<int> &a, int i, int l, int r) {
    if (r - l == 1) {
        tree[i] = a[l];
        return;
    }
    int m = (l + r) / 2;
    buildMin(tree, a, i * 2, l, m);
    buildMin(tree, a, i * 2 + 1, m, r);
    tree[i] = min(tree[i * 2], tree[i * 2 + 1]);
}

int getLeftSmaller(int tree[], int i, int l, int r, int ql, int qv) {
    if (r <= ql) {
        return nil;
    }
    if (l >= ql and tree[i] >= qv) {
        return r;
    }
    if (r - l == 1) {
        return l;
    }
    int m = (l + r) / 2;
    int f = getLeftSmaller(tree, i * 2, l, m, ql, qv);
    if (f != nil and f != m) {
        return f;
    }
    return getLeftSmaller(tree, i * 2 + 1, m, r, ql, qv);
}

int getRightSmaller(int tree[], int i, int l, int r, int qr, int qv) {
    if (l >= qr) {
        return nil;
    }
    if (r <= qr and tree[i] >= qv) {
        return l - 1;
    }
    if (r - l == 1) {
        return l;
    }
    int m = (l + r) / 2;
    int f = getRightSmaller(tree, i * 2 + 1, m, r, qr, qv);
    if (f != nil and f != m - 1) {
        return f;
    }
    return getRightSmaller(tree, i * 2, l, m, qr, qv);
}

void solve() {
    int n;
    cin >> n;
    n += 2;

    vector<int> v(n);
    v[0] = -1;
    v[n - 1] = -1;

    for (int i = 1; i < n - 1; i++) {
        cin >> v[i];
    }

    const int szH = 1e6 + 1;
    const int szT = 5e5;

    int heightsV[szH];
    memset(heightsV, 0, sizeof(heightsV));
    int heightsH[szH];
    memset(heightsH, 0, sizeof(heightsH));
    
    int treeV[szT];
    memset(treeV, 0, sizeof(treeV));
    buildMin(treeV, v, 1, 0, n);

    for (int i = 1; i < n - 1; i++) {
        int r = getLeftSmaller(treeV, 1, 0, n, i + 1, v[i]);
        int l = getRightSmaller(treeV, 1, 0, n, i + 1, v[i]);
        heightsV[v[i]] = max(heightsV[v[i]], r - (l + 1));
    }
    vector<int> h(n);
    h[0] = -1;
    h[n - 1] = -1;

    for (int i = 1; i < n - 1; i++) {
        cin >> h[i];
    }
    int treeH[szT];
    memset(treeH, 0, sizeof(treeH));
    buildMin(treeH, h, 1, 0, n);

    for (int i = szH - 2; i >= 0; i--) {
        heightsV[i] = max(heightsV[i], heightsV[i + 1]);
    }

    int ans = 0;
    for (int i = 1; i < n - 1; i++) {
        int r = getLeftSmaller(treeH, 1, 0, n, i + 1, h[i]);
        int l = getRightSmaller(treeH, 1, 0, n, i + 1, h[i]);
        heightsH[h[i]] = max(heightsH[h[i]], r - (l + 1));
        ans = max(ans, (r - (l + 1)) * h[i] * heightsV[h[i]]);
    }
    for (int i = szH - 2; i >= 0; i--) {
        heightsH[i] = max(heightsH[i], heightsH[i + 1]);
    }
    for (int i = 1; i < n - 1; i++) {
        ans = max(ans, v[i] * heightsH[v[i]] * heightsV[v[i]]);
    }
    cout << ans << '\n';
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

// 3:36:10 - 100